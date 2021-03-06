
#include "symbols.hh"
#include <cassert>
#include <iostream>
#include <li/sql/pgsql.hh>

using namespace s;

/* Mysql setup script:

CREATE TABLE users
(
id int,
name varchar(255),
age int
);
INSERT into users(id, name, age) values (1, "John", 42);
INSERT into users(id, name, age) values (2, "Bob", 24);
*/

// inline double get_time_in_seconds()
// {
//   timespec ts;
//   clock_gettime(CLOCK_REALTIME, &ts);
//   return double(ts.tv_sec) + double(ts.tv_nsec) / 1000000000.;
// }

int main() {
  using namespace li;

  // try
  {
    auto m = pgsql_database(s::host = "localhost", s::database = "postgres", s::user = "postgres",
                            s::password = "lithium_test", s::port = 32768, s::charset = "utf8");

    auto c = m.connect();

    c("DROP table if exists users_test_mysql;");
    //c("CREATE TABLE users_test_mysql (id SERIAL,name varchar(255),age int,login varchar(255));");
    c("CREATE TABLE if not exists users_test_mysql (id  SERIAL , age INT, name TEXT, login TEXT);");

    // // Prepared statement.
    // auto insert_user = c.prepare("INSERT into users_test_mysql(name, age, login) VALUES ($1,$2,$3) returning id;");
    // insert_user("John", 42, "login");
    // std::cout << "id: " << insert_user.last_insert_id() << std::endl;
    // insert_user("Bob", 24, "login"); // Send two queries.
    // std::cout << "id: " << insert_user.last_insert_id() << std::endl;

    // insert_user(1, "John", 42);
    auto insert_user = c.prepare("INSERT into users_test_mysql(id, age, name, login) VALUES ($1, $2, $3, $4) returning id");
    insert_user(1, 12, "Bob", "45");
    std::cout << "id: " << insert_user.last_insert_id() << std::endl;
    //std::cout 
    int count = c.prepare("SELECT count(*) from users_test_mysql;")().template read<int>();
    std::cout << count << std::endl;

    c.prepare("SELECT name, age from users_test_mysql")().map([] (std::string name, int age)
    {
      std::cout << "name: "<< name << " age:" << age << std::endl;
    });

    // int count = c("SELECT count(*) from users_test_mysql;").template read<int>();
    // std::cout << count << std::endl;
    //  assert(count == 2);

    // // multiple inserts.
    // //c("INSERT into users(id, name, age) values", users);

    // typedef decltype(mmm(s::id = int(), s::age = uint32_t(),  s::name = std::string())) User;

    // auto print = [] (User res) {
    //   std::cout << res.id << " - " << res.name << " - " << res.age << std::endl;
    // };

    // int test;
    // c("SELECT 1 + 2") >> test;
    // std::cout << test << std::endl;
    // assert(test == 3);

    // int count = 0;
    // c("SELECT count(*) from users") >> count;
    // std::cout << count << " users" << std::endl;

    // std::string b = "Bob";

    // User res;

    // double t = get_time_in_seconds();
    // int K = 200;

    // auto rq = c.prepare("SELECT * from users where name = ? and age = ? LIMIT 1");
    // for (int i = 0; i < K; i++)
    //   rq("Bob", 24) >> res;
    // std::cout << (1000 * (get_time_in_seconds() - t)) / K << std::endl;

    // t = get_time_in_seconds();

    // for (int i = 0; i < K; i++)
    //   c("SELECT * from users where name = ? and age = ? LIMIT 1")("Bob", 24) >> res;

    // std::cout << (1000 * (get_time_in_seconds() - t)) / K << std::endl;

    // if (!(c("SELECT * from users where name = ? and age = ?")("Bob", 24) >> res))
    //   throw http_error::not_found("User not found.");

    // int age;
    // std::string name;
    // if (!(c("SELECT age, name from users where name = ? and age = ?")("Bob", 24) >> std::tie(age,
    // name)))
    //   throw http_error::not_found("User not found.");
    // std::cout << name << " " << age  << std::endl;

    // print(res);

    // // Print the list of users
    // c("SELECT * from users") | print;

    // c("SELECT name, age from users") | [] (std::tuple<std::string, int>& r)
    // {
    //   std::cout << std::get<0>(r) << " " << std::get<1>(r) << std::endl;
    // };

    // c("SELECT age from users") | [] (int& r)
    // {
    //   std::cout << r << std::endl;
    // };

    // c("SELECT name, age from users") | [] (const std::string& name, const int& age)
    // {
    //   std::cout << name << " " << age << std::endl;
    // };

    // c("SELECT name, age from users") | [] (std::string& name, int& age)
    // {
    //   std::cout << name << " " << age << std::endl;
    // };

    // c("SELECT name, age from users") | [] (std::string name, int age)
    // {
    //   std::cout << name << " " << age << std::endl;
    // };
    // c("INSERT into users(name, age) VALUES (?, ?)")("John", 42);
  }
  // catch(const std::exception& e)
  // {
  //   std::cout << "error during test: " << e.what() << std::endl;
  //   return 1;
  // }
}
