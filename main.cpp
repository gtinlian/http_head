#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define HEADR_LEN 20

class http_head {
public:
    char skip;
    int row_skip[HEADR_LEN];  //冒号位置
    int list[HEADR_LEN];  //请求头行首位置
    int list_len;  //请求头行数
    int len;  //请求头限制

    http_head():list_len(0),len(2000){}

    int head_skip(char *buff, int start) {
        for (int i = start; buff[i] < len; i++) {
            if (buff[i] == '\r') {
                if (buff[i + 1] == '\n') {
                    if (buff[i + 2] == '\r') {
                        if (buff[i + 3] == '\n')
                            return -(i + 2);    //当返回负数时请求头解析结束
                    } else {
                        //头文件没结束
                        return i + 2;
                    }
                }
            }
        }
    }   //请求头切割

    int head_part( char *buff) {
        int start = 0;
        int i = 0;
        list[0] = 0;
        start = head_skip(buff, start);
        i++;
        list[i] = start;
        while (true) {
            start = head_skip(buff, start + 3);
            if (start < 0) {
                i++;
                list[i] = -start;
                list_len = i-1;
                return i;
            }
            i++;
            list[i] = start;
        }
    }   //请求头分段

};

int main() {

    char buffs[] = "Accept: */*\r\n"
                            "Accept-Encoding: gzip, deflate, br\r\n"
                            "Cache-Control: max-age=0\r\n"
                            "Host: mbd.baidu.com\r\n"
                            "Accept-Language: zh-CN,zh;q=0.9,en;q=0.8\r\n\r\n";
    http_head t;
    //FILE *fp = fopen("/root/test","a+");
    printf("%ld\n",time(NULL));
    for(int x = 0;x<10000000;x++) {
        t.head_part(buffs);
        //for (int i = 0; i <= t.list_len; i++) {
            //fwrite(buffs + t.list[i], t.list[i + 1] - t.list[i], 1, fp);
            //fflush(fp);
        //}
    }
    //valgrind --tool=memcheck --leak-check=full --show-reachable=yes  /tmp/tmp.jDd3LKrSx0/cmake-build-debug/untitled4
    printf("%ld\n",time(NULL));

    //fclose(fp);
    return 0;


}
