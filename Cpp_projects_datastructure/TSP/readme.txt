/*******************************************************************************
 * 在完成本作业的过程中，我从以下各位那里得到过以下方面的启发和帮助：
自02班剡航同学的思路及方法
 * 在我提交的程序中，还在对应的位置以注释形式记录了他们的具体帮助。
 *******************************************************************************
 * 我参考了以下资料：
邓俊辉老师BFS算法的模板
 * 在我提交的程序中，还在对应的位置以注释形式记录了具体的参考内容。
 *******************************************************************************
 * 我独立完成了本程序除以上方面之外的所有工作，包括分析、设计、编码、调试与测试。
 * 我清楚地知道，从以上方面获得的信息在一定程度上降低了作业难度，可能影响起评分。
 *******************************************************************************
 * 我从未抄袭或盗用过他人的程序，不管是原封不动地复制，还是经过了某些等价转换。
 * 我未曾也不会向同一课程（包括此后各届）的同学复制或公开我这份程序的代码。
 * 我编写这个程序无意于破坏或妨碍任何计算机系统的正常运转。
 * 我清楚地知道，以上情况均为本课程纪律所禁止，若违反，对应的作业成绩将按-100计。
 *******************************************************************************
 * 【周嘉莉】
 * 【2010010359】
 * 【2012-12-6】
 ******************************************************************************/
【算法实现】使用邻接表记录存贮村庄两点的ID和村庄之间的权值。采用广度搜索，利用邓俊辉老师的模板BFS。先任取一点，搜索到它的距离最远的点（带权值）i，点i必然是关键路径上的一个最远点。再以该点为起始点搜索离他距离最远的点（带权值），所得到的一定是donfood即最远路径。
【遇到的问题】最开始做的时候忽略了如果是广度搜索一定要用队列而不是栈，我选成了栈，结果错误。改了好久之后经同学提醒才了解到这一情况。。。
【时间复杂度分析】o(n)，广搜了两遍，每个节点被访问了两次，相当于o(2n)
【空间复杂度分析】o(n),邻接表实现存储空间恰巧是2n个节点
