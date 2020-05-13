#include <iostream>
#include <string.h>
#include <map>

#define HEADR_LEN 20

int head_skip(char *buff,int start){
    for(int i = start; buff[i] != '\n';i++){
        if(buff[i] == '\r'){
            if(buff[i+1] == '\n'){
                if(buff[i+2] == '\r'){
                    if(buff[i+3] == '\n')
                        return -(i+2);    //当返回负数时请求头解析结束
                }else{
                    //头文件没结束
                    return i + 2;
                }
            }
        }
    }
}   //请求头切割
int head_part(int *list,char *buff){
    int start = 0;
    int i = 0;
    list[0] = 0;
    start = head_skip(buff,start);
    i++;
    list[i] = start;
    while(true) {
        start = head_skip(buff, start + 3);
        if(start < 0){
            return i;
        }
        i++;
        list[i] = start;
    }
}   //请求头分段


int main() {
    char buffs[] = "Accept: */*\r\n"
                            "Accept-Encoding: gzip, deflate, br\r\n"
                            "Cache-Control: max-age=0\r\n"
                            "Host: mbd.baidu.com\r\n"
                            "Accept-Language: zh-CN,zh;q=0.9,en;q=0.8\r\n\r\n";
    int list[HEADR_LEN];
    int len = head_part(list,buffs);
    for(int i = 0;i <= len;i++) {
        printf("%s", buffs + list[i]);
    }


}
