#include <memory>
/******************************************************

std::shared_ptr< class > ���ȗ����邽�߂Ɏg�p����

******************************************************/

#ifndef PTR
#define PTR( NAME )\
	class NAME;\
	typedef std::shared_ptr< NAME > NAME##Ptr;\
	typedef std::shared_ptr< const NAME > NAME##ConstPtr;\
	typedef std::weak_ptr< NAME > NAME##WeakPtr;\
	typedef std::unique_ptr< NAME > NAME##UniquePtr;\

#endif

#ifndef STRUCT_PTR
#define STRUCT_PTR( NAME )\
	struct NAME;\
	typedef std::shared_ptr< NAME > NAME##Ptr;\
	typedef std::shared_ptr< const NAME > NAME##ConstPtr;\
	typedef std::weak_ptr< NAME > NAME##WeakPtr;\
	typedef std::unique_ptr< NAME > NAME##UniquePtr;\

#endif