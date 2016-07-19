/**
 * Created by KICT-20 on 2016-07-19.
 */
let arr_test=['banana','apple','mango','grape'];

console.log(arr_test)
arr_test.splice(
    2,  //삽입위치
    0,  //삭제 원소 갯수
    "melon","plum"  //삽입 문자
)
console.log(arr_test);
arr_test.splice(2,1);
console.log(arr_test)