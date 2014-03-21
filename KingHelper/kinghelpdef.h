#ifndef KINGHELPDEF_H
#define KINGHELPDEF_H


typedef struct productItem
{
   QString productName;
   QString productCode;
   QString productPrice;
   QString productUrl1;
   QString productUrl2;
   QString productUrl3;
   QString productImage;
   QString productDesc;
   QString productNamePY;
}productItem;


//数据库相关语句

//创建本地个人会话表
const QString createProductTable = "create table if not exists t_products(ID INTEGER PRIMARY KEY AUTOINCREMENT,productName varchar,productCode varchar,productPrice varchar,productUrl1 varchar,productUrl2 varchar,productUrl3 varchar,productImage varchar,prodectDesc varchar,prodectNamePY varchar)";

//查找群聊所有记录
const QString getallproducts = "select * from t_products";

//群聊历史记录表插入一条新的数据
const QString insertnewproductitem = "insert into t_products(ID,productName,productCode ,productPrice ,productUrl1 ,productUrl2 ,productUrl3 ,productImage ,prodectDesc,prodectNamePY ) values(?,?,?,?,?,?,?,?,?,?)";

//3.根据首拼,汉字,号码,账号模糊查询匹配到的成员id列表
const QString sql_get_userlist_by_pinyhead = "select * from T_IM_UserInfo where USER_NAME_PINYIN like '?%' or NAME like '?%' or USER_NAME like '?%' or MOBILE like '?%'or NAME like '%?' or NAME like '%?%'";

#endif // KINGHELPDEF_H
