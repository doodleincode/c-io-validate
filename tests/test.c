#include <stdio.h>
#include <stdlib.h>
#include "../../c-functions/include/io_lib.h"
#include "../../c-hashtable/include/hashtable.h"
#include "../include/io_validate.h"

int main()
{
    Status status;
    char buff[100];
    
    // Setup configuration for validating alphabetic characters
    Hashtable *config = init_hashtable();
    config->add(config, "min_chars", "4");
    config->add(config, "max_chars", "10");
    
    // Instantiate the validation class with configuration and validation type
    IOValidate *v = init_validate(config, VALIDATE_ALPHA);
    
    /*
    // Setup configuration for validating alphanum characters with specific chars
    Hashtable *config = init_hashtable();
    config->add(config, "min_chars", "4");
    config->add(config, "max_chars", "10");
    config->add(config, "allowed_chars", "abcd");
    
    // Instantiate the validation class with configuration and validation type
    IOValidate *v = init_validate(config, VALIDATE_ALPHANUM);
    */
    
    /*
    // Setup configuration for validating numbers
    Hashtable *config = init_hashtable();
    config->add(config, "min_num", "10");
    config->add(config, "max_num", "1000");
    
    // Instantiate the validation class with configuration and validation type
    IOValidate *v = init_validate(config, VALIDATE_NUM);
    */
    
    // Get user input
    fgets(buff, sizeof(buff), stdin);
    
    // Test the user provided input with our validation
    if (v->isvalid(v, &status, buff)) {
        printf("Validated!\n");
    }
    else {
        printf("Status code: %d\n", status.code);
        printf("Status msg: %s\n", status.msg);
    }
    
    release(v);
    free_hashtable(config);
    
    return 0;
}

