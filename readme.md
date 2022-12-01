# AoC 22

I had the (possibly dumb) idea of using this year's Advent of Code as an opportunity to teach myself C. I'm hoping at least some of my C# knowledge will translate.

## Day 1
- Reading a file line-by-line. This isn't too hard, but not sure if I did it in the most efficient way. 
- I actually got the correct answer before my code was completely working for Part 2. I wasn't doing any sorting when checking the highest value in the array. This meant I wasn't actually replacing the lowest value, just the first value that was lower than the new value. The input data was written such that the sorting happened automatically and my code returned the correct value even though the logic was wrong. I tested with a few changes to the dataset and everything seems to be working correctly now.