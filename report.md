edf report

输入格式：
    第一行一个数字n，表示一共n个任务
    接下来n行每行三个数字i,j,k，i表示任务请求时间，j表示任务执行时间，k表示任务绝对截止时间

设计思路：
    实际系统不可能提前预知有任务请求的发生，这里只是一种模拟，当任务请求时间大于当前时间是不对该任务进行处理
    实际系统的调度是当有任务请求时，检查该任务的优先级（根据edf）是否能够打断当前任务，然而程序已经提前给出了全部任务请求，因而只能采用时间片来进行模拟，每个时间片都进行一次任务选择，任务变化时进行输出，从而模拟实际系统的调度
    对于最后的三个数据，响应时间=处理机第一次调度任务的时间-任务请求时间，周转时间=任务完成时间-任务请求时间，等待时间=周转时间-任务执行时间，当任务没有被别的高优先级任务抢占时，响应时间=等待时间

测试用例与分析：
    Input：
    3
    0 10 30
    4 3 10
    5 10 25
    可以看出处理机先执行第一个任务，直到第四个时间片结束时新任务的请求打断当前任务，处理机保存当前任务（该时间被调度算法忽略）并执行新任务，第五个时间片结束后，虽有新任务请求，但被edf算法特性忽略，第七个时间片结束任务执行完，再执行第三个任务，最后还原并执行第一个任务。
    而程序执行的结果如下：
    Execution trace:
    execute quest[0] in time [0,4), quest length:10, have done:4, quest interrupted
    execute quest[1] in time [4,7), quest length:3, have done:3, quest done
    execute quest[2] in time [7,17), quest length:10, have done:10, quest done
    execute quest[0] in time [17,23), quest length:10, have done:10, quest done
    statistics:
    quest[0]: reponse 0 turnaround 23 wait 13
    quest[1]: reponse 0 turnaround 3 wait 0
    quest[2]: reponse 2 turnaround 12 wait 2
    average -- response 0.67 turnaround 12.67 wait 5.00
    可见程序在这一用例上是正确的。