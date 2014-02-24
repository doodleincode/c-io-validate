c-io-validate
=============

IO validation library for C. This library allows you to easily validate user input from stdin.

The library can be extended by using your own custom validation functions.

Usage
-------------

This library depends on various libraries from my other repositories:

* [c-hashtable](https://github.com/hongmeister/c-hashtable)
* [c-functions](https://github.com/hongmeister/c-functions)
  * class.c
  * status_lib.c
  * stype.c

View the test.c script in ./tests/ for example usage to get started.

Extend the library with your own validation functions
-------------

Simply create a new function with the following prototype:

  <code>int FUNCTION_NAME(IOValidate *, Status *, const char *)</code>

Then pass the function name as a pointer to the instantiation function, like so:

  <code>init_validate(Hashtable *, FUNCTION_NAME)</code>

You can also accept user configured parameters. Simple create a Hashtable configuration variable:

    Hashtable *config = init_hashtable();
    config->add(config, "param_name", "value");

Then pass it to the validation instantiation function:

  <code>init_validate(config, FUNCTION_NAME)</code>

Then in your validation function, you can use the parameter(s) like this:

  <code>this->\_config->get(this->\_config, "your_param_name");</code>

