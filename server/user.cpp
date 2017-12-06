# include "user.h"


  User::User(QString name, int point)
      : name_(name), point_(point), status_(Wait) {}

  User::~User() {}

  User::GameStatus User::get_status() const
  {
     return status_;
  }

  void User::set_status(GameStatus status) {
     status_ = status;
  }

  void User::set_point(int point) {
     point_ = point;
  }

  int User::get_point() const
  {
     return point_;
  }
  QString User::get_name() const
  {
       return name_;
  }
