#include "rmw/error_handling.h"
#include "rmw/rmw.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "std_msgs/msg/string.hpp"
//#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"

#include "std_msgs/msg/string.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"

#if 0
#define puts(...)
#define printf(...)
#endif

static const char * fake_impl_id = "fake";

static char fake_buffer[128] = { 0 };
static bool fake_new = false;

const char *
rmw_get_implementation_identifier(void)
{
  puts("rmw_get_implementation_identifier");
  return NULL;
}

rmw_ret_t
rmw_init(void)
{
  puts("rmw_init");
  return RMW_RET_OK;
}

rmw_node_t *
rmw_create_node(const char * name, size_t domain_id)
{
  (void) name;
  (void) domain_id;
  puts("rmw_create_node");
  rmw_node_t *node = (rmw_node_t *)malloc(sizeof(rmw_node_t));
  node->implementation_identifier = fake_impl_id;
  node->data = NULL;
  node->name = name;
  return node;
}

rmw_ret_t
rmw_destroy_node(rmw_node_t * node)
{
  (void) node;
  puts("rmw_destroy_node");
  return RMW_RET_OK;
}

const rmw_guard_condition_t *
rmw_node_get_graph_guard_condition(const rmw_node_t * node)
{
  (void) node;
  puts("rmw_node_get_graph_guard_condition");
  rmw_guard_condition_t * ret = (rmw_guard_condition_t *)malloc(sizeof(rmw_guard_condition_t));
  ret->data = NULL;
  ret->implementation_identifier = fake_impl_id;
  return ret;
}

rmw_publisher_t *
rmw_create_publisher(
  const rmw_node_t * node,
  const rosidl_message_type_support_t * type_support,
  const char * topic_name,
  const rmw_qos_profile_t * qos_policies)
{
  (void) node;
  (void) type_support;
  (void) topic_name;
  (void) qos_policies;
  puts("rmw_create_publisher");
  rmw_publisher_t * ret = (rmw_publisher_t *)malloc(sizeof(rmw_publisher_t));
  ret->data = NULL;
  ret->implementation_identifier = fake_impl_id;
  ret->topic_name = topic_name;
  return ret;
}

rmw_ret_t
rmw_destroy_publisher(rmw_node_t * node, rmw_publisher_t * publisher)
{
  (void) node;
  (void) publisher;
  puts("rmw_destroy_publisher");
  return RMW_RET_OK;
}

rmw_ret_t
rmw_publish(const rmw_publisher_t * publisher, const void * ros_message)
{
  (void) publisher;
  (void) ros_message;
  puts("rmw_publish");

  std_msgs__msg__String* msg = (std_msgs__msg__String*)ros_message;
  printf("msg: %s\n", msg->data.data);
  strcpy(fake_buffer, msg->data.data);

  //std_msgs::msg::String* msg = (std_msgs::msg::String*)ros_message;
  //printf("msg: %s\n", msg->data.c_str());
  //strcpy(fake_buffer, msg->data.c_str());
  
  fake_new = true;

  return RMW_RET_OK;
}

rmw_subscription_t *
rmw_create_subscription(
  const rmw_node_t * node,
  const rosidl_message_type_support_t * type_support,
  const char * topic_name,
  const rmw_qos_profile_t * qos_policies,
  bool ignore_local_publications)
{
  (void) node;
  (void) type_support;
  (void) topic_name;
  (void) qos_policies;
  (void) ignore_local_publications;
  puts("rmw_create_subscription");
  rmw_subscription_t * ret = (rmw_subscription_t *)malloc(sizeof(rmw_subscription_t));
  ret->data = NULL;
  ret->implementation_identifier = fake_impl_id;
  ret->topic_name = topic_name;

  printf("type_support->typesupport_identifier: %s\n", type_support->typesupport_identifier);

  //const rosidl_typesupport_introspection_cpp::MessageMembers *ts_data = (const rosidl_typesupport_introspection_cpp::MessageMembers *)type_support->data;
  const rosidl_typesupport_introspection_c__MessageMembers *ts_data = (const rosidl_typesupport_introspection_c__MessageMembers *)type_support->data;

  printf("ts_data->package_name_: %s\n", ts_data->package_name_);
  printf("ts_data->message_name_: %s\n", ts_data->message_name_);
  printf("ts_data->member_count_: %i\n", (int)ts_data->member_count_);

  for(size_t i = 0 ; i < ts_data->member_count_ ; i++) {
    printf("ts_data->members_[%i]:\n", (int)i);
    printf("\tname_: %s\n", ts_data->members_[i].name_);
    printf("\tmembers_: %p\n", (void*)ts_data->members_[i].members_);
  }

  //while(1);

  return ret;
}

rmw_ret_t
rmw_destroy_subscription(rmw_node_t * node, rmw_subscription_t * subscription)
{
  (void) node;
  (void) subscription;
  puts("rmw_destroy_subscription");
  return RMW_RET_OK;
}

rmw_ret_t
rmw_take(const rmw_subscription_t * subscription, void * ros_message, bool * taken)
{
  (void) subscription;
  (void) ros_message;
  (void) taken;
  puts("rmw_take");
  return RMW_RET_OK;
}

rmw_ret_t
rmw_take_with_info(
  const rmw_subscription_t * subscription,
  void * ros_message,
  bool * taken,
  rmw_message_info_t * message_info)
{
  (void) subscription;
  (void) ros_message;
  (void) taken;
  (void) message_info;
  puts("rmw_take_with_info");

  printf("subscription: %p\n", (void*)subscription);
  printf("ros_message: %p\n", (void*)ros_message);
  printf("taken: %p\n", (void*)taken);
  printf("message_info: %p\n", (void*)message_info);

  *taken = true;

  std_msgs__msg__String* msg = (std_msgs__msg__String*)ros_message;
  msg->data.data = fake_buffer;
  msg->data.size = strlen(fake_buffer);

  //std_msgs::msg::String* msg = (std_msgs::msg::String*)ros_message;
  //msg->data = fake_buffer;

  return RMW_RET_OK;
}

rmw_client_t *
rmw_create_client(
  const rmw_node_t * node,
  const rosidl_service_type_support_t * type_support,
  const char * service_name,
  const rmw_qos_profile_t * qos_policies)
{
  (void) node;
  (void) type_support;
  (void) service_name;
  (void) qos_policies;
  puts("rmw_create_client");
  return NULL;
}

rmw_ret_t
rmw_destroy_client(rmw_node_t * node, rmw_client_t * client)
{
  (void) node;
  (void) client;
  puts("rmw_destroy_client");
  return RMW_RET_OK;
}

rmw_ret_t
rmw_send_request(
  const rmw_client_t * client,
  const void * ros_request,
  int64_t * sequence_id)
{
  (void) client;
  (void) ros_request;
  (void) sequence_id;
  puts("rmw_send_request");
  return RMW_RET_OK;
}

rmw_ret_t
rmw_take_response(
  const rmw_client_t * client,
  rmw_request_id_t * request_header,
  void * ros_response,
  bool * taken)
{
  (void) client;
  (void) request_header;
  (void) ros_response;
  (void) taken;
  puts("rmw_take_response");
  return RMW_RET_OK;
}

rmw_service_t *
rmw_create_service(
  const rmw_node_t * node,
  const rosidl_service_type_support_t * type_support,
  const char * service_name,
  const rmw_qos_profile_t * qos_policies)
{
  (void) node;
  (void) type_support;
  (void) service_name;
  (void) qos_policies;
  puts("rmw_create_service");
  return NULL;
}

rmw_ret_t
rmw_destroy_service(rmw_node_t * node, rmw_service_t * service)
{
  (void) node;
  (void) service;
  puts("rmw_destroy_service");
  return RMW_RET_OK;
}

rmw_ret_t
rmw_take_request(
  const rmw_service_t * service,
  rmw_request_id_t * request_header,
  void * ros_request,
  bool * taken)
{
  (void) service;
  (void) request_header;
  (void) ros_request;
  (void) taken;
  puts("rmw_take_request");
  return RMW_RET_OK;
}

rmw_ret_t
rmw_send_response(
  const rmw_service_t * service,
  rmw_request_id_t * request_header,
  void * ros_response)
{
  (void) service;
  (void) request_header;
  (void) ros_response;
  puts("rmw_send_response");
  return RMW_RET_OK;
}

rmw_guard_condition_t *
rmw_create_guard_condition(void)
{
  puts("rmw_create_guard_condition");
  rmw_guard_condition_t * ret = (rmw_guard_condition_t *)malloc(sizeof(rmw_guard_condition_t));
  ret->data = NULL;
  ret->implementation_identifier = fake_impl_id;
  return ret;
}

rmw_ret_t
rmw_destroy_guard_condition(rmw_guard_condition_t * guard_condition)
{
  (void) guard_condition;
  puts("rmw_destroy_guard_condition");
  free(guard_condition);
  return RMW_RET_OK;
}

rmw_ret_t
rmw_trigger_guard_condition(const rmw_guard_condition_t * guard_condition)
{
  (void) guard_condition;
  puts("rmw_trigger_guard_condition");
  return RMW_RET_OK;
}

rmw_waitset_t *
rmw_create_waitset(size_t max_conditions)
{
  (void) max_conditions;
  puts("rmw_create_waitset");
  rmw_waitset_t * ret = (rmw_waitset_t *)malloc(sizeof(rmw_waitset_t));
  ret->data = NULL;
  ret->guard_conditions = NULL;
  ret->implementation_identifier = fake_impl_id;
  return ret;
}

rmw_ret_t
rmw_destroy_waitset(rmw_waitset_t * waitset)
{
  (void) waitset;
  puts("rmw_destroy_waitset");
  free(waitset);
  return RMW_RET_OK;
}

rmw_ret_t
rmw_wait(
  rmw_subscriptions_t * subscriptions,
  rmw_guard_conditions_t * guard_conditions,
  rmw_services_t * services,
  rmw_clients_t * clients,
  rmw_waitset_t * waitset,
  const rmw_time_t * wait_timeout)
{
  (void) subscriptions;
  (void) guard_conditions;
  (void) services;
  (void) clients;
  (void) waitset;
  (void) wait_timeout;
  puts("rmw_wait");

  printf("timeout: %p\n", (void*)wait_timeout);

  printf("subscriptions:    %4i\n", (int)subscriptions->subscriber_count);
  for(size_t i = 0 ; i < subscriptions->subscriber_count ; i++) {
    printf("\t[%i] => %p\n", (int)i, (void*)subscriptions->subscribers[i]);
    if(fake_new) {
      subscriptions->subscribers[i] = (void*)1;
      fake_new = false;
    }
  }

  printf("guard_conditions: %4i\n", (int)guard_conditions->guard_condition_count);
  for(size_t i = 0 ; i < guard_conditions->guard_condition_count ; i++) {
    printf("\t[%i] => %p\n", (int)i, (void*)guard_conditions->guard_conditions[i]);
  }

  printf("services:         %4i\n", (int)services->service_count);
  for(size_t i = 0 ; i < services->service_count ; i++) {
    printf("\t[%i] => %p\n", (int)i, (void*)services->services[i]);
  }

  printf("clients:          %4i\n", (int)clients->client_count);
  for(size_t i = 0 ; i < clients->client_count ; i++) {
    printf("\t[%i] => %p\n", (int)i, (void*)clients->clients[i]);
  }

  return RMW_RET_OK;
}

rmw_ret_t
rmw_get_topic_names_and_types(
  const rmw_node_t * node,
  rmw_topic_names_and_types_t * topic_names_and_types)
{
  (void) node;
  (void) topic_names_and_types;
  puts("rmw_get_topic_names_and_types");
  return RMW_RET_OK;
}

rmw_ret_t
rmw_destroy_topic_names_and_types(
  rmw_topic_names_and_types_t * topic_names_and_types)
{
  (void) topic_names_and_types;
  puts("rmw_destroy_topic_names_and_types");
  return RMW_RET_OK;
}

rmw_ret_t
rmw_count_publishers(
  const rmw_node_t * node,
  const char * topic_name,
  size_t * count)
{
  (void) node;
  (void) topic_name;
  (void) count;
  puts("rmw_count_publishers");
  return RMW_RET_OK;
}

rmw_ret_t
rmw_count_subscribers(
  const rmw_node_t * node,
  const char * topic_name,
  size_t * count)
{
  (void) node;
  (void) topic_name;
  (void) count;
  puts("rmw_count_subscribers");
  return RMW_RET_OK;
}

rmw_ret_t
rmw_get_gid_for_publisher(const rmw_publisher_t * publisher, rmw_gid_t * gid)
{
  (void) publisher;
  (void) gid;
  puts("rmw_get_gid_for_publisher");
  return RMW_RET_OK;
}

rmw_ret_t
rmw_compare_gids_equal(const rmw_gid_t * gid1, const rmw_gid_t * gid2, bool * result)
{
  (void) gid1;
  (void) gid2;
  (void) result;
  puts("rmw_compare_gids_equal");
  return RMW_RET_OK;
}

rmw_ret_t
rmw_service_server_is_available(
  const rmw_node_t * node,
  const rmw_client_t * client,
  bool * is_available)
{
  (void) node;
  (void) client;
  (void) is_available;
  puts("rmw_service_server_is_available");
  return RMW_RET_OK;
}
