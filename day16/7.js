/**
 * Created by KICT-20 on 2016-07-19.
 */

let arr_test=['banana','apple',"orange",'grape','melon'];
console.log(arr_test);
arr_test.push('watermelon');
console.log(arr_test);

console.log('추출'+arr_test.shift());
console.log(arr_test);

arr_test.unshift('strawberry');
console.log(arr_test);

console.log('추출'+arr_test.pop());
console.log(arr_test);