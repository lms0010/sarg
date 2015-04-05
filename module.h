#ifndef MODULE_H
#define MODULE_H

class Module {
public:
    virtual bool          update() = 0;
    virtual const char*   getLastError() = 0;
    virtual bool          initialize() = 0;
    virtual bool          uninitialize() = 0;
};


#endif // MODULE_H
