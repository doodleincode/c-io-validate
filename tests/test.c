#include <stdio.h>
#include <stdlib.h>
#include "../../c-functions/include/io_lib.h"
#include "../../c-hashtable/include/hashtable.h"
#include "../include/io_validate.h"

int main()
{
    Status status;
    char buff[100];
    
    // Setup configuration for the validation
    Hashtable *config = init_hashtable();
    config->add(config, "min_chars", "4");
    config->add(config, "max_chars", "10");
    //config->add(config, "allowed_chars", "abcd");
    //config->add(config, "min_num", "10");
    //config->add(config, "max_num", "1000");
    
    // Instantiate the validation class with configuration and validation type
    IOValidate *v = init_validate(config, VALIDATE_ALPHA);
    //IOValidate *v = init_validate(config, VALIDATE_ALPHANUM);
    //IOValidate *v = init_validate(config, VALIDATE_NUM);
    
    // Get user input
    io_fgets(NULL, buff, sizeof(buff), stdin);
    
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

