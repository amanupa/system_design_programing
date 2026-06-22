#pragma once

class ITransport{
    public:
    virtual ~ITransport()=default;
    virtual void delivery()=0;
};