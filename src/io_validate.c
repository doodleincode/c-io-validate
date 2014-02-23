/**
 * Library to perform basic validation on user input from stdin
 *
 * @author  Daniel Hong
 * 
 * This program is licensed under the GNU GENERAL PUBLIC LICENSE Version 2.
 * A LICENSE file should have accompanied this program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "../include/io_validate.h"
#include "../../c-hashtable/include/hashtable.h"
#include "../../c-functions/include/stype.h"

IOValidate *init_validate(Hashtable *cfg, void *validate_func)
{
    IOValidate *v;
    
    if ((v = malloc(sizeof(IOValidate))) == NULL) {
        return NULL;
    }
    
    // Setup the "public" function pointers
    v->isvalid = validate_func;
    
    // Private members
    v->__cfg__ = cfg;
    v->__validate_string__ = _validate_string;
    v->__isvalidlen__ = _isvalidlen;
    
    return v;
}

// -----------------------------------------------------------------------------
//  These are accessible through the isvalid() method.
//
//  You can write your own validation functions using the following prototype:
//
//     int FUNCTION_NAME(IOValidate *, Status *, const char *)
//
//  Your validation function can accept user provided configuration as a 
//  Hashtable structure
// -----------------------------------------------------------------------------
 
static int VALIDATE_ALPHA(IOValidate *this, Status *status, const char *buff)
{
    return this->__validate_string__(this, status, buff, TYPE_ALPHA);
}

static int VALIDATE_ALPHANUM(IOValidate *this, Status *status, const char *buff)
{
    return this->__validate_string__(this, status, buff, TYPE_ALPHANUM);
}

static int VALIDATE_NUM(IOValidate *this, Status *status, const char *buff)
{
    double min_num;
    double max_num;
    double input;
    
    // Check if number first
    if (is_number(buff) == 0) {
        status_set(status, STATUS_INVALID_INPUT, "Input was not a valid number.");
        return 0;
    }
    
    // Make sure the number isn't larger than the size of a double so that
    // we don't run into undefined behaviors when converting the string to a double
    if (strlen(buff) > (sizeof(double) * 8)) {
        status_set(status, STATUS_INVALID_INPUT, "Input was larger than a double.");
        return 0;
    }
    
    // We're going to convert the string buffer to a double so that we can
    // test for floating point numbers as well
    input = atof(buff);
    
    min_num = atof(this->__cfg__->get(this->__cfg__, "min_num", "0"));
    max_num = atof(this->__cfg__->get(this->__cfg__, "max_num", "0"));
    
    // Check if we are validating against min or max number
    if ((min_num != 0 && input < min_num) || (max_num != 0 && input > max_num)) {
        // If max number was not set, we need to show a different message
        if (max_num == 0) {
            status_format_msg(status, 
                        STATUS_INVALID_INPUT, "Number must be greater than %.2f.", min_num);
        }
        else {
            status_format_msg(status, 
                        STATUS_INVALID_INPUT, 
                        "Number outside of allowed range of %.2f to %.2f.", 
                        min_num, max_num);
        }
        
        return 0;
    }
    
    return 1;
}

// -----------------------------------------------------------------------------
//  Private function pointer implementations.
// -----------------------------------------------------------------------------

// Helper function to check if we are validating against char length
static int _isvalidlen(IOValidate *this, Status *status, const char *buff)
{
    int buffsize = strlen(buff);
    int min_chars = atoi(this->__cfg__->get(this->__cfg__, "min_chars", "0"));
    int max_chars = atoi(this->__cfg__->get(this->__cfg__, "max_chars", "0"));
    
    // Check if we are validating for min length. If true, check the length
    if (min_chars > 0 && buffsize < min_chars) {
        status_format_msg(status, 
                            STATUS_INVALID_INPUT, 
                            "Input requires at least %d characters.", 
                            min_chars);
        return 0;
    }
    // If we are validating for max length. If true, check the length
    else if (max_chars > 0 && buffsize > max_chars) {
        status_format_msg(status, 
                            STATUS_INVALID_INPUT, 
                            "Input cannot exceed %d characters.", 
                            max_chars);
        return 0;
    }
    
    return 1;
}

// Helper function to validate against alpha and alphanum
static int _validate_string(IOValidate *this, Status *status, const char *buff, int type)
{
    // Check input length validation
    if (! this->__isvalidlen__(this, status, buff)) {
        return 0;
    }
    
    int i;
    
    if (buff) {
        for (i = 0; buff[i]; i++) {
            // Skipping NULL, newline, space, tab (respectively)
            if ((int)buff[i] == 0 || (int)buff[i] == 10 || 
                (int)buff[i] == 32 || (int)buff[i] == 9)
            {
                continue;
            }
            
            // Checking alpha
            if (type == TYPE_ALPHA && ! isalpha(buff[i])) {
                status_set(status, STATUS_INVALID_INPUT, 
                    "Only alphabetic characters are allowed.");
                return 0;
            }
            // Checking alphanum
            else if (type == TYPE_ALPHANUM && ! isalnum(buff[i])) {
                status_set(status, STATUS_INVALID_INPUT, 
                    "Only alphanumeric characters are allowed.");
                return 0;
            }
            
            const char *allowed_chars = this->__cfg__->get(this->__cfg__, "allowed_chars", "");
            
            // Check if we are restricting the characters allowed
            // If we are, we'll test those characters with the input
            if (allowed_chars && 
                strlen(allowed_chars) > 0 &&
                strchr(allowed_chars, buff[i]) == NULL) 
            {
                status_set(status, STATUS_INVALID_INPUT, "Invalid characters.");
                return 0;
            }
        }
        
        return 1;
    }
    
    return 0;
}

