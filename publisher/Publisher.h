#ifndef publisher_h
#define publisher_h

namespace Publisher{

class PublisherBase{
public:
    virtual void publish_msg(void*) = 0;
    virtual void* serialize_msg(void*) = 0;
};

class lcmPublisher:public PublisherBase{
 public:
    void publish_msg(void*);
    void* serialize_msg(void*);
};

}

#endif
