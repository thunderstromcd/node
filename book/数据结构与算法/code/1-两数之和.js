function twoSum(nums, target) {
    let hash = {};
    for (let i = 0; i < nums.length; i++) {
        if (hash[target - nums[i]] !== undefined) {
            return [i, hash[target - nums[i]]];
        }
        hash[nums[i]] = i;
    }
    return [];
}

// var twoSum = function (nums, target) {
//     let hash = {};
//     for (let i = 0; i < nums.length; i++) {
//       if (hash[target - nums[i]] !== undefined) {
//         return [i, hash[target - nums[i]]];
//       }
//       hash[nums[i]] = i;
//     }
//     return [];
//   };


let res = twoSum([3, 3], 6)
console.log(res);