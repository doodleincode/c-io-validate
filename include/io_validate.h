/**
 * Library to perform basic validation on user input from stdin
 *
 * @author 	Daniel Hong
 * 
 * This program is licensed under the GNU GENERAL PUBLIC LICENSE Version 2.
 * A LICENSE file should have accompanied this program.
 */

#ifndef _DH_IO_VALIDATE_H_
#define _DH_IO_VALIDATE_H_

#include "../../c-functions/include/class.h"
#include "../../c-functions/include/status_lib.h"
#include "../../c-hashtable/include/hashtable.h"

#define TYPE_ALPHA    1
#define TYPE_ALPHANUM 2

CLASS(IOValidate,
    /**
     * Perform input validation on a given user input based on a given set
     * of validation parameters.
     *
     * See the the ./tests/test.c file for a usage example
     *
     * @param   IOValidate *    A pointer to an IOValidate structure created from
     *                          init_validate()
     * @param   Status *        A pointer to a Status structure. If you dont want
     *                          to check the status returned from this function, 
     *                          pass in a NULL
     * @param   const char *    The buffer to validate
     * @return  int             Returns 1 if validation succeeded based on the 
     *                          validation parameters. Returns 0 on validation failure
     */
    FUNC(int, isvalid, (struct IOValidate *, Status *, const char *));
    
    // -------------------------------------------------------------------------
    //  Below are private properties and methods
    //  These should not be used as they can change at any time without notice
    //  and as such are not documented
    // -------------------------------------------------------------------------
    
    Hashtable *_config;
    FUNC(int, _isvalidlen, (struct IOValidate *, Status *, const char *));
    FUNC(int, _validate_string, (struct IOValidate *, Status *, const char *, int));
);

/**
 * Instantiate an IOValidate structure. This function would be equivalent to 
 * the "new" keyword in C++. Objects created by this function must be released
 * when no longer used.
 *
 * @param   Hashtable *     The validation configuration hashtable
 * @return  IOValidate *    Pointer to an IOValidate structure. Returns
 *                          NULL on error.
 */
IOValidate *init_validate(Hashtable *, void *);

// -----------------------------------------------------------------------------
//  These are accessible through the isvalid() method and should not be 
//  called directly.
//
//  You can write your own validation functions using the following prototype:
//
//     int FUNCTION_NAME(IOValidate *, Status *, const char *)
//
//  Your validation function can accept user provided configuration as a 
//  Hashtable structure
// -----------------------------------------------------------------------------

int VALIDATE_ALPHA(IOValidate *, Status *, const char *);
int VALIDATE_ALPHANUM(IOValidate *, Status *, const char *);
int VALIDATE_NUM(IOValidate *, Status *, const char *);

// -----------------------------------------------------------------------------
//  Function pointers. These are private functions and cannot be called directly
// -----------------------------------------------------------------------------

static int _isvalidlen_(IOValidate *, Status *, const char *);
static int _validate_string_(IOValidate *, Status *, const char *, int);

#endif /* _DH_IO_VALIDATE_H_ */

