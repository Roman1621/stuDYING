#include "mainWindow.h"
#include <iostream>
#include "algorithm/perm_conv.h"
#include "algorithm/perm_ga.h"

int main(int argc, char *argv[])
{
  Permutation p;
  p.push_back(0);
  p.push_back(1);
  p.push_back(2);
  p.push_back(3);
  std::cout << perm_to_bool_string(p) << std::endl;
  std::cout << bool_string_to_perm(perm_to_bool_string(p), 4) << std::endl;
  std::vector<BoolString> vbs = generate_rand_perms(4, 10);
  for(size_t i = 0; i < vbs.size(); i++) std::cout << bool_string_to_perm(vbs[i], 4) << std::endl;
  
  /*
  auto app = Gtk::Application::create(argc, argv, "sum.project");

  MainWindow window;

  //Shows the window and returns when it is closed.
  return app->run(window);*/
}