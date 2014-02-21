c-io-validate
=============

IO validation library for C.

The library supports custom validation functions. Simply create a new function with the following prototype:

  int FUNCTION_NAME(IOValidate *, Status *, const char *)

Then pass the function name as a pointer to the instantiation function, like so:

  init_validate(Hashtable *, FUNCTION_NAME)

You can also accept user configured parameters. Simple create a Hashtable configuration variable:

  Hashtable *config = init_hashtable();
  config->add("param_name", "value");

Then pass it to the validation instantiation function:

  init_validate(config, FUNCTION_NAME)

Then in your validation function, you can use the parameter(s) like this:

  this->__cfg__->get(this->__cfg__, "your_param_name");

