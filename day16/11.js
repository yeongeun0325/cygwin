/**
 * Created by KICT-20 on 2016-07-19.
 */

let arr_test=[
    {
        name:'ye',
        hp:23
    },
    {
        name:'mango',
        hp: 17
    },
    {
        name:'coffe',
        hp: 10
    },
    {
        name:'candy',
        hp: 25
    },
];

console.log(arr_test);

arr_test.sort((left,right)=>{
    return right.hp-left.hp;
    //return left.hp-right.hp;
});
console.log(arr_test);