#include "main.h"

using namespace std;

enum
{
  max_length = 1024
};

bool use_ssl = false;
std::unique_ptr<tcp::Client> proto;

co::Pool pool(
    []()
    { return (void *)new tcp::Client(*proto); },
    [](void *p)
    { delete (tcp::Client *)p; });

void client_fun()
{
  co::PoolGuard<tcp::Client> c(pool);

  if (!c->connect(3000))
  {
    LOG_S(WARNING) << "connect failed: " << c->strerror();
    LOG_S(INFO) << "connect failed: " << c->strerror();
    return;
  }

  char buf[8] = {0};

  while (true)
  {
    LOG_S(INFO) << "client send ping";
    int r = c->send("ping", 4);
    if (r == 4)
    {
      LOG_S(INFO) << "send ok, num:" << r << "\n";
    }

    if (r <= 0)
    {
      LOG_S(INFO) << "client send error: " << c->strerror();
      break;
    }

    // r = c->recv(buf, 8);
    r = c->recv(buf, 100);
    LOG_S(INFO) << "received , num:" << r << "buf:" << buf << "\n";
    if (r < 0)
    {
      LOG_S(INFO) << "client recv error: " << c->strerror();
      break;
    }
    else if (r == 0)
    {
      LOG_S(INFO) << "server close the connection";
      break;
    }
    else
    {
      LOG_S(INFO) << "client recv " << fastring(buf, r) << '\n';
      co::sleep(3000);
    }
  }
}
struct test
{
  double d{0.1234567890};
  float  f{1.234};
};

test t;


int tcp_client_coro()
{

 LOG_S(INFO) << "tcp client start ."<< "\n";

LOG_S(INFO) << fmt::format("struct d={},f={} .",t.d,t.f);
char byte_test[20]{0};
std::memcpy(byte_test,&t,sizeof(t));
int i{0};
	while (i <= sizeof(byte_test)/sizeof(int))
    {
     LOG_S(INFO) << fmt::format("byte_test[{}] ={} .",i,byte_test[i]);

      	i++;
    }
    std::memset(&t,0,sizeof(t));
    LOG_S(INFO) << fmt::format("struct d={},f={} .",t.d,t.f);
    std::memcpy(&t,byte_test,sizeof(t));
    LOG_S(INFO) << fmt::format("struct d={},f={} .",t.d,t.f);
  // proto.reset(new tcp::Client("192.168.0.110", 56050, use_ssl));

  // for (int i = 0; i < 1; ++i)
  // {
  //   go(client_fun);
  //  LOG_S(INFO) << "tcp client fun ." << i << "\n";
  // }
  return 0;
}
