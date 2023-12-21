#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "input.c"

struct department{
    char *id;
    char *name;
    char *class;
};

struct club{
    char *id;
    char *name;
};

struct course{
    char *id;
    char *name;
};
/*
   当前使用者的账号信息
*/
struct account{
    char *id;
    char *name;
    char *password;
    struct department departments[3][100];
    struct course courses[3][100];
    struct club clubs[3][100];
};
struct account user;
int num[3][3];

sqlite3 *db;

const char *column_name[3] = { "学号", "姓名", "密码" };
#include "login.c"
#include "refresh.c"
#include "account.c"
#include "send.c"
int Len = 0 , cnt = 0;
#include "withdraw.c"

/*
int main( int argc, char *argv[] ){
    int err = 0;
    char *errmsg;
    
    err = sqlite3_open( "C2.db", &db );
    if( err!=0 ){
      fprintf( stderr, "无法打开数据库: %s\n", sqlite3_errmsg(db) );
      sqlite3_close(db);
      return(1);
    }
    else{
      fprintf(stdout,"成功打开数据库\n");
    }
    err = sqlite3_exec( db, "PRAGMA foreign_keys=true;", NULL, NULL, &errmsg );
    exec_report( err, errmsg, "无法设置外键", "成功设置外键", 1, 0 );
    while( user.id == NULL ){
        char a = 2;
        while( a!='e' && a!='0' && a!='1' ){
            printf( "\n选择登录或注册(0: 登录, 1: 注册, e: 退出程序): " );
            a = getchar();
            clear_input_buffer();
        }
        switch(a){
            case '0':{
                err = login();
                break;
            }
            case '1':{
                err = regist();
                break;
            }
            case 'e':{
                user.id = "exit";
                return 0;
            }
        }
    }
    if( err ){
        return 1;
    }
    refresh();

    while(1) {
        char a = 2;
        while(a != '0' && a != '1' && a != 'e') {
            printf("\n选择功能(0: 发信息, 1: 查看收件箱, e: 退出程序): ");
            a = getchar();
            clear_input_buffer();
        }
        switch(a) {
            case '0':{
                err = Send(); break;
            }
            case '1':{
                err = Receive(); break;
            }
            case 'e':{
                id = "exit";
                return 0;
            }
        }

    }
    return 0;
}
*/

int main(){
    int err = -1;
    char *errmsg = NULL, c;

    err = sqlite3_open( "C2.db", &db );
    if( err!=0 ){
        printf("无法打开数据库: %s\n", sqlite3_errmsg(db) );
        sqlite3_close(db);
        return 1;
    }
    else{
        printf("成功打开数据库\n");
    }
    err = sqlite3_exec( db, "PRAGMA foreign_keys=true;", NULL, NULL, &errmsg );
    if( err!=0 ){
        printf( "无法设置外键: %s\n", errmsg );
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return 1;
    }
    else{
        printf("成功设置外键\n");
    }
    while( err==-1 ){
        while( user.id == NULL ){
            c = 2;
            while( c!='e' && c!='0' && c!='1' ){
                printf( "\n选择登录或注册(0: 登录, 1: 注册, e: 退出程序): " );
                c = getchar();
                clear_input_buffer();
            }
            switch(c){
                case '0':{
                    login();
                    break;
                }
                case '1':{
                    regist();
                    break;
                }
                case 'e':{
                    user.id = "exit";
                    return 0;
                }
            }
        }
        err = refresh();
        if(err){
            return err;
        }
        err = -1;
        while( err==-1 ){
            printf("----------菜单----------\n");
            if( (user.departments[0][0]).id==NULL && (user.courses[0][0]).id==NULL && (user.clubs[0][0]).id==NULL ){
                while( c!='e' && c!='3' && c!='1' && c!='2' ){
                    printf("1: 详细查询通知\n2: 修改密码\n3: 注销用户\ne: 登出\n");
                    c = getchar();
                    clear_input_buffer();
                }
            }
        }
    }
}