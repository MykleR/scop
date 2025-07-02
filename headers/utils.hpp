#pragma once

#include <stdexcept>
#include <iostream>

# define COMMA	,

# define UNUSED(x) ((void)x)

# define FIELD(type, var) \
	private: type var; \

# define GETSET(cls, type, var, ...) \
	private: type _##var; \
	public: \
	const type& get_##var() const {return _##var;} \
	cls& set_##var(const type& val) {_##var = val; __VA_ARGS__ return *this;}

# define GETTER(type, var) \
	private: type _##var; \
	public: const type& get_##var() const {return _##var;}

# define SETTER(cls, type, var, ...) \
	private: type _##var; \
	public: cls& set_##var(type val) {_##var = val; __VA_ARGS__ return *this;}

# define EXCEPTION(name, msg)												\
class name : public std::exception {										\
	inline const char *what() const throw() { return (msg) ; } ; }

# define EXCEPTION_MSG(name)												\
class name : public std::exception {										\
	private: std::string msg;												\
	public:																	\
    explicit name(const std::string& m) : msg(m) {}							\
    virtual ~name() throw() {}												\
    virtual const char* what() const throw() {return msg.c_str();}			\
};
