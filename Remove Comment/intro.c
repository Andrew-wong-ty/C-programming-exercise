//在引号中的情况
const char* case1 = "//asd\nasd"; //dasd"
const char* case2 = "/*asdasd*/"; /*
*multi*
* 多行注释
* \
*/
/*123*/
// 嵌套注释
float case3 = /*hi*/1.0/*hi*//9/*hi*/+2/*hi*/;  
int case4 = 1+/*hi*/ \ 
2;
