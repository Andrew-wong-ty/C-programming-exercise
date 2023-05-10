#include<stdarg.h>
#include<stdio.h>

void minprintf(char* format, ...) {
    va_list ap; // 用于指向参数列表总的参数
    va_start(ap, format); // 初始化ap指向第一个参数
    int va_int;
    double va_double;
    char* va_str_ptr;
    char* fmt_p;
    for(fmt_p = format;*fmt_p!='\0';fmt_p++) {
        if(*fmt_p!='%') {
            // 非控制符：直接输出
            putchar(*fmt_p);
            continue;
        } else {
            if(*(++fmt_p)!='\0') {
                switch (*fmt_p)
                {
                    case 'd':
                    {
                        va_int = va_arg(ap,int);
                        printf("%d", va_int);
                        break;
                    }
                    case 'f':
                    {
                        va_double = va_arg(ap, double);
                        printf("%f", va_double);
                        break;
                    }
                    case 's':
                    {
                        for(va_str_ptr = va_arg(ap, char*);*va_str_ptr!='\0';va_str_ptr+=1) {
                            putchar(*va_str_ptr);
                        }
                        break;
                    }
                    
                    default:
                    {
                        putchar(*fmt_p);
                        break;
                    }
                }
            }
        }
        
    }
    va_end(ap);
    
    
}

int main(int argc, char const *argv[])
{
    minprintf("int:%d, float:%f, string:%s,%%\n",1, 4.999, "asdasd");
    return 0;
}
