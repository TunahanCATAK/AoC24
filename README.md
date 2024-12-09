# AoC24
Advent of Code 2024 


run the code with the following command: 
```bash
python3 createProj.py
```

<style>
.calendar .calendar-color-8n { color:#886655; }
.calendar .calendar-color-2g2 { color:#7fbd39; }
.calendar .calendar-color-3i { color:#a25151; }
.calendar .calendar-color-3m { color:#d4dde4; }
.calendar .calendar-color-3s { color:#e3b585; }
.calendar .calendar-color-2u { color:#5eabb4; }
.calendar .calendar-color-6t { color:#aaaaaa; }
.calendar .calendar-color-6o { color: #ff9900; text-shadow: 0 0 5px #ff9900; }
.calendar .calendar-color-2g0 { color:#488813; }
.calendar .calendar-color-3v { color:#df2308; text-shadow:0 0 5px #df2308, 0 0 10px #df2308; }
.calendar .calendar-color-3l { color:#ccccff; }
.calendar .calendar-color-2g3 { color:#427322; }
.calendar .calendar-color-2g1 { color:#4d8b03; }
.calendar .calendar-color-8i { color:#ff0000; text-shadow:0 0  5px #ff0000, 0 0 10px #ff0000, 0 0 15px #ff0000; }
.calendar .calendar-color-2w { color:#ffffff; }
.calendar .calendar-color-3b { color:#5555bb; }
.calendar .calendar-color-8w { color:#cccccc; }
.calendar .calendar-color-w { color: #ccc; }
.calendar .calendar-color-3w { color:#ffffff; }
.calendar .calendar-color-6u { color: #0066ff; text-shadow: 0 0 5px #0066ff; }
.calendar .calendar-color-6y { color:#ffff66; text-shadow:0 0 5px #ffff66; }
.calendar .calendar-color-6r { color: #ff0000; text-shadow: 0 0 5px #ff0000; }
.calendar .calendar-color-3y { color:#ffff66; text-shadow:0 0 5px #ffff66, 0 0 10px #ffff66; }
.calendar .calendar-color-8e { color:#cccccc; }
.calendar .calendar-color-6b { color:#009900; }
.calendar .calendar-color-3a { color:#a5a8af; }
.calendar .calendar-color-3g { color:#00cc00; }
</style>

# Advent of Code 2024 Tree: 

<br> 
<pre class="calendar">          .-----.          .------------------.         
<a aria-label="Day 1, two stars" href="https://adventofcode.com/2024/day/1" class="calendar-day1 calendar-verycomplete">       <span class="calendar-color-w">.--'</span><span class="calendar-color-3s">~</span> <span class="calendar-color-3s">~</span> <span class="calendar-color-3s">~</span><span class="calendar-color-w">|</span>        <span class="calendar-color-w">.-'</span> <span class="calendar-color-6y">*</span>       <span class="calendar-color-8n">\</span>  <span class="calendar-color-8n">/</span>     <span class="calendar-color-w">'-.</span>  <span class="calendar-day"> 1</span> <span class="calendar-mark-complete">*</span><span class="calendar-mark-verycomplete">*</span></a>
<a aria-label="Day 2, two stars" href="https://adventofcode.com/2024/day/2" class="calendar-day2 calendar-verycomplete">    <span class="calendar-color-w">.--'</span><span class="calendar-color-3s">~</span>  <span class="calendar-color-3g">,</span><span class="calendar-color-3y">*</span> <span class="calendar-color-3s">~</span> <span class="calendar-color-w">|</span>        <span class="calendar-color-w">|</span>  <span class="calendar-color-6b">&gt;</span><span class="calendar-color-6o">o</span><span class="calendar-color-6b">&lt;</span>   <span class="calendar-color-8n">\_\_\|_/__/</span>   <span class="calendar-color-w">|</span>  <span class="calendar-day"> 2</span> <span class="calendar-mark-complete">*</span><span class="calendar-mark-verycomplete">*</span></a>
<a aria-label="Day 3, two stars" href="https://adventofcode.com/2024/day/3" class="calendar-day3 calendar-verycomplete"><span class="calendar-color-w">.---'</span><span class="calendar-color-3s">:</span> <span class="calendar-color-3s">~</span> <span class="calendar-color-3g">'</span><span class="calendar-color-3b">(~)</span><span class="calendar-color-3g">,</span> <span class="calendar-color-3s">~</span><span class="calendar-color-w">|</span>        <span class="calendar-color-w">|</span> <span class="calendar-color-6b">&gt;</span><span class="calendar-color-6r">@</span><span class="calendar-color-6b">&gt;</span><span class="calendar-color-6u">O</span><span class="calendar-color-6b">&lt;</span> <span class="calendar-color-8i">o</span><span class="calendar-color-8n">-_/</span><span class="calendar-color-8e">.</span><span class="calendar-color-8w">()</span><span class="calendar-color-8n">__------</span><span class="calendar-color-w">|</span>  <span class="calendar-day"> 3</span> <span class="calendar-mark-complete">*</span><span class="calendar-mark-verycomplete">*</span></a>
<a aria-label="Day 4, two stars" href="https://adventofcode.com/2024/day/4" class="calendar-day4 calendar-verycomplete"><span class="calendar-color-w">|</span><span class="calendar-color-2g1">@</span><span class="calendar-color-2u">..</span><span class="calendar-color-2g2">@</span><span class="calendar-color-3s">'.</span> <span class="calendar-color-3s">~</span> <span class="calendar-color-3g">"</span> <span class="calendar-color-3g">'</span> <span class="calendar-color-3s">~</span> <span class="calendar-color-w">|</span>        <span class="calendar-color-w">|</span><span class="calendar-color-6b">&gt;</span><span class="calendar-color-6u">O</span><span class="calendar-color-6b">&gt;</span><span class="calendar-color-6o">o</span><span class="calendar-color-6b">&lt;</span><span class="calendar-color-6r">@</span><span class="calendar-color-6b">&lt;</span> <span class="calendar-color-8n">\____</span>       <span class="calendar-color-3g">.'</span><span class="calendar-color-w">|</span>  <span class="calendar-day"> 4</span> <span class="calendar-mark-complete">*</span><span class="calendar-mark-verycomplete">*</span></a>
<a aria-label="Day 5, two stars" href="https://adventofcode.com/2024/day/5" class="calendar-day5 calendar-verycomplete"><span class="calendar-color-w">|</span><span class="calendar-color-2g3">_</span><span class="calendar-color-2u">.~.</span><span class="calendar-color-2g3">_@</span><span class="calendar-color-3s">'..</span> <span class="calendar-color-3s">~</span> <span class="calendar-color-3s">~</span> <span class="calendar-color-3y">*</span><span class="calendar-color-w">|</span>        <span class="calendar-color-w">|</span> <span class="calendar-color-6t">_|</span> <span class="calendar-color-6t">|_</span>    <span class="calendar-color-w">..</span><span class="calendar-color-8w">\_</span><span class="calendar-color-8n">\_</span> <span class="calendar-color-3g">..'</span><span class="calendar-color-3y">*</span> <span class="calendar-color-w">|</span>  <span class="calendar-day"> 5</span> <span class="calendar-mark-complete">*</span><span class="calendar-mark-verycomplete">*</span></a>
<a aria-label="Day 6, two stars" href="https://adventofcode.com/2024/day/6" class="calendar-day6 calendar-verycomplete"><span class="calendar-color-w">|</span> <span class="calendar-color-2w">|||</span> <span class="calendar-color-2g2">@@</span>  <span class="calendar-color-3s">'''...</span><span class="calendar-color-w">|</span>        <span class="calendar-color-w">|</span><span class="calendar-color-3i">...</span>     <span class="calendar-color-w">.'</span>  <span class="calendar-color-w">'.</span><span class="calendar-color-3g">'''..</span><span class="calendar-color-3m">/</span><span class="calendar-color-3g">..</span><span class="calendar-color-w">|</span>  <span class="calendar-day"> 6</span> <span class="calendar-mark-complete">*</span><span class="calendar-mark-verycomplete">*</span></a>
<a aria-label="Day 7, two stars" href="https://adventofcode.com/2024/day/7" class="calendar-day7 calendar-verycomplete"><span class="calendar-color-w">|</span><span class="calendar-color-2g3">@</span><span class="calendar-color-2w">~~~</span><span class="calendar-color-2g2">@</span><span class="calendar-color-2g3">@</span><span class="calendar-color-2g1">#</span><span class="calendar-color-2g3">@</span><span class="calendar-color-2g2">#</span>  <span class="calendar-color-2g0">@</span>   <span class="calendar-color-w">|</span>        <span class="calendar-color-w">|</span><span class="calendar-color-3a">/\</span> <span class="calendar-color-3i">''.</span>  <span class="calendar-color-w">|</span>    <span class="calendar-color-w">|</span>   <span class="calendar-color-3l">-</span><span class="calendar-color-3m">/</span>  <span class="calendar-color-3w">:</span><span class="calendar-color-w">|</span>  <span class="calendar-day"> 7</span> <span class="calendar-mark-complete">*</span><span class="calendar-mark-verycomplete">*</span></a>
<a aria-label="Day 8, two stars" href="https://adventofcode.com/2024/day/8" class="calendar-day8 calendar-verycomplete"><span class="calendar-color-w">|</span><span class="calendar-color-2u">~~.</span><span class="calendar-color-w">.--.</span> _____  <span class="calendar-color-w">|</span>        <span class="calendar-color-w">|</span><span class="calendar-color-3y">*</span> <span class="calendar-color-3a">/</span><span class="calendar-color-3v">~</span><span class="calendar-color-3a">\</span> <span class="calendar-color-3i">'.</span><span class="calendar-color-w">|</span>    <span class="calendar-color-w">|</span> <span class="calendar-color-3l">-</span> <span class="calendar-color-3m">/</span>  <span class="calendar-color-3w">.'</span><span class="calendar-color-w">|</span>  <span class="calendar-day"> 8</span> <span class="calendar-mark-complete">*</span><span class="calendar-mark-verycomplete">*</span></a>
<a aria-label="Day 9, two stars" href="https://adventofcode.com/2024/day/9" class="calendar-day9 calendar-verycomplete"><span class="calendar-color-w">'---'</span>  <span class="calendar-color-w">|</span>|[][]_\-<span class="calendar-color-w">|</span>        <span class="calendar-color-w">|</span><span class="calendar-color-3v">~</span><span class="calendar-color-3a">/</span> <span class="calendar-color-3y">*</span> <span class="calendar-color-3a">\</span> <span class="calendar-color-3i">:</span><span class="calendar-color-w">|</span>    <span class="calendar-color-w">|</span>  <span class="calendar-color-3y">*</span><span class="calendar-color-3w">..'</span>  <span class="calendar-color-w">|</span>  <span class="calendar-day"> 9</span> <span class="calendar-mark-complete">*</span><span class="calendar-mark-verycomplete">*</span></a>
<span aria-hidden="true" class="calendar-day9">'---'  |        |        |        |    |        |  <span class="calendar-day"> 10</span><span id="calendar-countdown">16:52:49</span><script>
(function(){
var countdown = document.getElementById("calendar-countdown");
if (!countdown) return;
var server_eta = 60832;
var key = "2024-9-"+server_eta;
var now = Math.floor(new Date().getTime()/1000);
var target = server_eta + now;
if (sessionStorage) {
  // if you navigate away and hit the back button, this makes sure the countdown doesn't start from the wrong time
  var prev_target = sessionStorage.getItem("calendar-target");
  try { prev_target = JSON.parse(prev_target); } catch(e){}
  if (prev_target && typeof prev_target === 'object' && prev_target.key === key) {
    target = prev_target.target;
  } else {
    sessionStorage.setItem("calendar-target", JSON.stringify({key:key, target:target+1}));
  }
}

var interval = null;
function update_countdown() {
  var remaining = Math.ceil(target - new Date().getTime()/1000);
  if (remaining <= 0) {
    clearInterval(interval);
    interval = null;
    countdown.textContent = "";

    var a = document.createElement("a");
    a[String.fromCharCode(104,114,101,102)] = "/2024" + String.fromCharCode(47,100,97,121,47) + "9";
    a.className = "calendar-day9 calendar-day-new";
    var span = countdown.parentNode;
    while (span.firstChild) {
      a.appendChild(span.firstChild);
    }
    a.appendChild(document.createTextNode("   "));
    span.parentNode.insertBefore(a, span);
    span.parentNode.removeChild(span);
    countdown.parentNode.removeChild(countdown);
  } else {
    var hours = Math.floor(remaining/60/60);
    remaining -= hours * 60 * 60;
    var minutes = Math.floor(remaining/60);
    remaining -= minutes * 60;
    var seconds = remaining;
    countdown.textContent = (hours < 10 ? "0" : "") + hours + ":" + (minutes < 10 ? "0" : "") + minutes + ":" + (seconds < 10 ? "0" : "") + seconds;
  }
}
interval = setInterval(update_countdown,1000);
update_countdown();
})();
</script></span>
<span aria-hidden="true" class="calendar-day11">                                                   <span class="calendar-day">11</span></span>
<span aria-hidden="true" class="calendar-day12">                                                   <span class="calendar-day">12</span></span>
<span aria-hidden="true" class="calendar-day13">                                                   <span class="calendar-day">13</span></span>
<span aria-hidden="true" class="calendar-day14">                                                   <span class="calendar-day">14</span></span>
<span aria-hidden="true" class="calendar-day15">                                                   <span class="calendar-day">15</span></span>
<span aria-hidden="true" class="calendar-day16">                                                   <span class="calendar-day">16</span></span>
<span aria-hidden="true" class="calendar-day17">                                                   <span class="calendar-day">17</span></span>
<span aria-hidden="true" class="calendar-day18">                                                   <span class="calendar-day">18</span></span>
<span aria-hidden="true" class="calendar-day19">                                                   <span class="calendar-day">19</span></span>
<span aria-hidden="true" class="calendar-day20">                                                   <span class="calendar-day">20</span></span>
<span aria-hidden="true" class="calendar-day21">                                                   <span class="calendar-day">21</span></span>
<span aria-hidden="true" class="calendar-day22">                                                   <span class="calendar-day">22</span></span>
<span aria-hidden="true" class="calendar-day23">                                                   <span class="calendar-day">23</span></span>
<span aria-hidden="true" class="calendar-day24">                                                   <span class="calendar-day">24</span></span>
<span aria-hidden="true" class="calendar-day25">                                                   <span class="calendar-day">25</span></span>
</pre>
</br> 



## Day 1: 

## Day 2: 
_bool isSafe(const std::vector<int>& values)_ function time complexity analysis:

In the first question: 

- std::adjacent_difference --> O(n)
- std::find_if --> O(n)
- std::all_of --> O(n)

but there is no nested loops, so the overall time complexity is **O(n)**

In the second question:

- std::adjacent_difference --> O(n)
- std::find_if --> O(n)
- std::all_of --> O(n)

but this time, we have the nested loop to calculate subVector's safety, so the overall time complexity is **O(n<sup>2</sup>)**

Ideas to apply: 
- create an async function to calculate the safety of the subVector and have a 
thread pool to run while reading values from the input.txt. Something like Producer/Consumer. 

## Day 3:

Created a _co-routine based lazy file reading_ utility function. 
Which reads a file line by line and waits the caller to ask for the next line.
Tried to implement a kind of generator function in C++.

## Day 5: 
Tried to solve the problem with recursive function, but it was not efficient. I got 
a stack overflow error. So, I had to change the approach. 

Then I decided to use std::is_sorted() function. Which provides us a special comparison function.
But the time complexity of the solution became O(n<sup>2</sup>).
O(n) for the is_sorted function and O(n) for the comparison function.

## Day 6:
I've solved the second problem with a brute force approach, with adding '#' to all possible positions and find out to loop with iterating through the maze. 
There can be some nicer solutions with graphs, investigate it. 


## Day 8: 
Range based permutator function is implemented to generate all possible permutations of a given range.
This still needs to be improved and tested. But I am going to move it to my utility library. 


