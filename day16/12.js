/**
 * Created by KICT-20 on 2016-07-19.
 */

let arr_test=[52,101,32,45,73,270,129,63];
console.log(arr_test);

//100이상 수만 골라서 지우기
/*
for(let i=0;i<arr_test.length;i++){
    if(arr_test[i]<100){
        console.log(arr_test[i]);
    }
}
*/

for(let i=0;i<arr_test.length;i++){
    if(arr_test[i]>100){
        arr_test.splice(i,1);
        i--;
    }
}
console.log(arr_test)

for(let i=arr_test;i>=0;i--){
    if(arr_test[i]>100){
        arr_test.splice(i,1);
    }
}

console.log(arr_test)