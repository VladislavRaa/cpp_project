#ifndef USER_H
#define USER_H

#include <QDataStream>
#include <iostream>
//#include "myserver.h"



class User {
 public:
  User(QString name = "None", int point = 0);

  ~User();

  friend QDataStream& operator >>(QDataStream &out, User & user);

  enum GameStatus {Wait = 0, Go = 1};

  GameStatus get_status() const;

  void set_status(GameStatus status);

  void set_point(int point);

  int get_point() const;

  QString get_name() const;


private:
 QString name_;
 GameStatus status_;
 int point_;

};

inline QDataStream& operator >>(QDataStream &out, User & user)
{
     out >> user.name_;
     //out >> user.status_;
     out >> user.point_;
     return out;
}

#endif // USER_H

