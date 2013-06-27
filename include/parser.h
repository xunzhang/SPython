#ifndef PARSER_H 
#define PARSER_H

#include <string>
#include <iostream>
#include <stdlib.h>
#include <map>
#include <stdio.h>

#include "pyobject.h"
#include "intobject.h"
#include "stringobject.h"
#include "dictobject.h"

const char* info = "SPython 0.0.1 (default, June 25 2013, 11:09:15) \nType 'exit' to exit\n";
const char* prompt = ">>> ";

class engine
{
public:
  
  engine() {
    dict_obj = new PyDictObject;
    global_map = (PyObject *)dict_obj;
  }
  
  void exec() {
    std::cout << info;
    std::cout << prompt;
    while(getline(std::cin, command)) {
      if(command.size() == 0) {
        std::cout << prompt;
        continue;
      } else if(command == "exit") return;
      else {
        parserandexec(command);
      }
      std::cout << prompt;
    }
  }

private:

  void parserandexec(std::string& cmd) {
    std::string::size_type pos = 0;
    // a little slow, debug mode
    checklegel(cmd);
    if((pos = cmd.find("print ")) != std::string::npos) {
      std::string tmp = cmd.substr(6);
      print(tmp);
    }
    else if((pos = cmd.find(" = ")) != std::string::npos) {
      std::string v = cmd.substr(0, pos);
      std::string w = cmd.substr(pos + 3);
      assignoradd(v, w);
    } else {
      std::cout << "Can not recognize: " << cmd << std::endl;
      exit(1);
    }
  }
  
  // notice: no '&' symbol
  // no flexiable, can not support case: print "spython", TBO
  PyObject* getobj(std::string varname) {
    PyObject *key = PyStr_Create(varname.c_str()); 
    PyObject *val = PyDict_GetItem(global_map, key);
    if(val == NULL) {
      std::cout << "NameError: name '" << varname << "' is not defined" << std::endl;
      exit(1);
    }
    return val;
  }

  void print(std::string& var) {
    PyObject *obj = getobj(var);
    (obj->ob_type)->tp_print(obj);
  }
  
  void assignoradd(std::string& left, std::string& right) {
    std::string::size_type pos = 0;
    PyObject *res = NULL;
    PyObject *rkey = PyStr_Create(right.c_str());
    PyObject *rval = PyDict_GetItem(global_map, rkey);

    if(rval != NULL) {
      // case: b = a
      // a is well defined before
      PyDict_SetItem(global_map, rkey, rval);
    } else if(isnum(right)) {
      // case: a = 123
      PyObject *key = PyStr_Create(left.c_str());
      PyObject *val = CreatePyIntObject(atoi(right.c_str()));
      PyDict_SetItem(global_map, key, val);
    } else if(right.find("\"") != std::string::npos || right.find("'") != std::string::npos) {
      // case: d = "python"
      PyObject *key = PyStr_Create(left.c_str());
      PyObject *val = PyStr_Create(right.substr(1, right.size() - 2).c_str());
      PyDict_SetItem(global_map, key, val);
    } else if((pos = right.find("+")) != std::string::npos) {
      // case: c = a + b
      PyObject *obj_a = getobj(right.substr(0, pos - 1));
      PyObject *obj_b = getobj(right.substr(pos + 2));
      if(obj_a != NULL && obj_b != NULL && obj_a->ob_type == obj_b->ob_type) {
        res = ((obj_a->ob_type)->tp_as_number)->add(obj_a, obj_b);
        // even if key exist, can be optimized
        PyObject *key = PyStr_Create(left.c_str());
        PyDict_SetItem(global_map, key, res);
      }
    } else {
      std::cout << "SyntaxError: invalid syntax" << std::endl;
      exit(1);
    }
  }
  
  bool isnum(std::string& s) {
    std::string::size_type len = s.size();
    for(std::string::size_type i = 0; i < len; ++i) {\
      if(!isdigit(s[i])) return false;
    }
    return true;
  }
  
  void checklegel(std::string& cmd) {
    // case: a + b = c + d
    std::string::size_type pos = 0;
    if((pos = cmd.find(" = ")) != std::string::npos) {
      std::string v = cmd.substr(0, pos);
      if((pos = v.find("+")) != std::string::npos) {
        std::cout << "SyntaxError: can't assign to operator" << std::endl;
        exit(1);
      }
    }
    
  }

private:
  PyDictObject *dict_obj;
  PyObject *global_map;
  std::string command;
};

#endif
