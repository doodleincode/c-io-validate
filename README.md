c-io-validate
=============

IO validation library for C.

The library supports custom validation functions. Simply create a new function with the following prototype:

  <code>int FUNCTION_NAME(IOValidate *, Status *, const char *)</code>

Then pass the function name as a pointer to the instantiation function, like so:

  <code>init_validate(Hashtable *, FUNCTION_NAME)</code>

You can also accept user configured parameters. Simple create a Hashtable configuration variable:

    Hashtable *config = init_hashtable();
    config->add("param_name", "value");

Then pass it to the validation instantiation function:

  <code>init_validate(config, FUNCTION_NAME)</code>

Then in your validation function, you can use the parameter(s) like this:

  <code>this->__cfg__->get(this->__cfg__, "your_param_name");</code>

