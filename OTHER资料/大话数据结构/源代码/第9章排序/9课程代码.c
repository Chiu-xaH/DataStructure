


#define MAXSIZE 10000  	/* 用于要排序数组个数最大值，可根据需要修改 */
typedef struct
{
	int r[MAXSIZE+1];	/* 用于存储要排序数组，r[0]用作哨兵或临时变量 */
	int length;			/* 用于记录顺序表的长度 */
}SqList;


/* 交换L中数组r的下标为i和j的值 */
void swap(SqList *L,int i,int j) 
{ 
	int temp=L->r[i]; 
	L->r[i]=L->r[j]; 
	L->r[j]=temp; 
}

/* 对顺序表L作交换排序（冒泡排序初级版） */
void BubbleSort0(SqList *L)
{ 
	int i,j;
	for(i=1;i<L->length;i++)
	{
		for(j=i+1;j<=L->length;j++)
		{
			if(L->r[i]>L->r[j])
			{
				 swap(L,i,j);	/* 交换L->r[i]与L->r[j]的值 */
			}
		}
	}
}

/* 对顺序表L作冒泡排序 */
void BubbleSort(SqList *L)
{ 
	int i,j;
	for(i=1;i<L->length;i++)
	{
		for(j=L->length-1;j>=i;j--) /* 注意j是从后往前循环 */
		{
			if(L->r[j]>L->r[j+1]) 	/* 若前者大于后者（注意这里与上一算法的差异）*/
			{
				 swap(L,j,j+1);		/* 交换L->r[j]与L->r[j+1]的值 */
			}
		}
	}
}

/* 对顺序表L作改进冒泡算法 */
void BubbleSort2(SqList *L)
{ 
	int i,j;
	Status flag=TRUE;					/* flag用来作为标记 */
	for(i=1;i<L->length && flag;i++) 	/* 若flag为true有数据交换，否则退出循环 */
	{
		flag=FALSE;						/* 初始为False */
		for(j=L->length-1;j>=i;j--)
		{
			if(L->r[j]>L->r[j+1])
			{
				swap(L,j,j+1);			/* 交换L->r[j]与L->r[j+1]的值 */
				flag=TRUE;				/* 如果有数据交换，则flag为true */
			}
		}
	}
}

/* 对顺序表L作简单选择排序 */
void SelectSort(SqList *L)
{
	int i,j,min;
	for(i=1;i<L->length;i++)
	{ 
		min = i;						/* 将当前下标定义为最小值下标 */
		for (j = i+1;j<=L->length;j++)	/* 循环之后的数据 */
        {
			if (L->r[min]>L->r[j])		/* 如果有小于当前最小值的关键字 */
                min = j;				/* 将此关键字的下标赋值给min */
        }
		if(i!=min)						/* 若min不等于i，说明找到最小值，交换 */
			swap(L,i,min);				/* 交换L->r[i]与L->r[min]的值 */
	}
}

void InsertSort(SqList *L) 			/* 对顺序表L作直接插入排序 */
{ 
	int i,j;
	for(i=2;i<=L->length;i++)
	{
		if (L->r[i]<L->r[i-1]) 		/* 需将L->r[i]插入有序子表 */
		{
			L->r[0]=L->r[i]; 		/* 设置哨兵 */
			for(j=i-1;L->r[j]>L->r[0];j--)
				L->r[j+1]=L->r[j]; 	/* 记录后移 */
			L->r[j+1]=L->r[0]; 		/* 插入到正确位置 */
		}
	}
}

void ShellSort(SqList *L) 					/* 对顺序表L作希尔排序 */
{
	int i,j,k=0;
	int increment=L->length;
	do
	{
		increment=increment/3+1;			/* 增量序列 */
		for(i=increment+1;i<=L->length;i++)
		{
			if (L->r[i]<L->r[i-increment])	/* 需将L->r[i]插入有序增量子表 */ 
			{ 
				L->r[0]=L->r[i]; 			/* 暂存在L->r[0] */
				for(j=i-increment;j>0 && L->r[0]<L->r[j];j-=increment)
					L->r[j+increment]=L->r[j]; /*  记录后移，查找插入位置 */
				L->r[j+increment]=L->r[0]; 	/*  插入 */
			}
		}
	}
	while(increment>1);
}



void HeapSort(SqList *L)		/* 对顺序表L进行堆排序 */
{
	int i;
	for(i=L->length/2;i>0;i--) 	/* 把L中的r构建成一个大顶堆 */
		HeapAdjust(L,i,L->length);
	for(i=L->length;i>1;i--)
	{ 
		swap(L,1,i); 			/* 将堆顶记录和当前未经排序子序列最后一记录交换 */
		HeapAdjust(L,1,i-1); 	/* 将L->r[1..i-1]重新调整为大顶堆 */
	}
}

void HeapAdjust(SqList *L,int s,int m)
{ /* 本函数调整L->r[s]的关键字，使L->r[s..m]成为一个大顶堆 */
	int temp,j;
	temp=L->r[s];
	for(j=2*s;j<=m;j*=2) 	/* 沿关键字较大的孩子结点向下筛选 */
	{
		if(j<m && L->r[j]<L->r[j+1])
			++j; 			/* j为关键字中较大的记录的下标 */
		if(temp>=L->r[j])
			break; 			/* rc应插入在位置s上 */
		L->r[s]=L->r[j];
		s=j;
	}
	L->r[s]=temp; 			/* 插入 */
}

/* 对顺序表L作归并排序 */
void MergeSort(SqList *L)
{ 
 	MSort(L->r,L->r,1,L->length);
}

/* 将SR[s..t]归并排序为TR1[s..t] */
void MSort(int SR[],int TR1[],int s, int t)
{
	int m;
	int TR2[MAXSIZE+1];
	if(s==t)
		TR1[s]=SR[s];
	else
	{
		m=(s+t)/2;				/* 将SR[s..t]平分为SR[s..m]和SR[m+1..t] */
		MSort(SR,TR2,s,m);		/* 递归地将SR[s..m]归并为有序的TR2[s..m] */
		MSort(SR,TR2,m+1,t);	/* 递归地将SR[m+1..t]归并为有序的TR2[m+1..t] */
		Merge(TR2,TR1,s,m,t);	/* 将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t] */
	}
}


void Merge(int SR[],int TR[],int i,int m,int n)
{ /* 将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n] */
	int j,k,l;
	for(j=m+1,k=i;i<=m && j<=n;k++)	/* 将SR中记录由小到大地并入TR */
	{
		if (SR[i]<SR[j])
			TR[k]=SR[i++];
		else
			TR[k]=SR[j++];
	}
	if(i<=m)
	{
		for(l=0;l<=m-i;l++)
			TR[k+l]=SR[i+l];		/* 将剩余的SR[i..m]复制到TR */
	}
	if(j<=n)
	{
		for(l=0;l<=n-j;l++)
			TR[k+l]=SR[j+l];		/* 将剩余的SR[j..n]复制到TR */
	}
}


void MergeSort2(SqList *L) 				 /* 对顺序表L作归并非递归排序 */
{
	int* TR=(int*)malloc(L->length * sizeof(int));	/* 申请额外空间 */
    int k=1;
	while(k<L->length)
	{
		MergePass(L->r,TR,k,L->length);
		k=2*k;										/* 子序列长度加倍 */
		MergePass(TR,L->r,k,L->length);
		k=2*k;										/* 子序列长度加倍 */       
	}
}


void MergePass(int SR[],int TR[],int s,int n)
{/* 将SR[]中相邻长度为s的子序列两两归并到TR[] */
	int i=1;
	int j;
	while(i <= n-2*s+1)					/* 两两归并 */
	{
		Merge(SR,TR,i,i+s-1,i+2*s-1);
		i=i+2*s;        
	}
	if(i<n-s+1) 						/* 归并最后两个序列 */
		Merge(SR,TR,i,i+s-1,n);
	else 								/* 若最后只剩下单个子序列 */
		for(j =i;j <= n;j++)
			TR[j] = SR[j];
}

/* 对顺序表L作快速排序 */
void QuickSort(SqList *L)
{ 
	QSort(L,1,L->length);
}

/* 对顺序表L中的子序列L->r[low..high]作快速排序 */
void QSort(SqList *L,int low,int high)
{ 
	int pivot;
	if(low<high)
	{
		/* 将L->r[low..high]一分为二，算出枢轴值pivot */
		pivot=Partition(L,low,high); 
		QSort(L,low,pivot-1);		 /*  对低子表递归排序 */
		QSort(L,pivot+1,high);		 /*  对高子表递归排序 */
	}
}

int Partition(SqList *L,int low,int high)
{/* 交换顺序表L中子表的记录，使枢轴记录到位，并返回其所在位置，此时在它之前(后)均不大(小)于它。*/
	int pivotkey;

	pivotkey=L->r[low]; 	/* 用子表的第一个记录作枢轴记录 */
	while(low<high) 		/* 从表的两端交替地向中间扫描 */
	{ 
		 while(low<high&&L->r[high]>=pivotkey)
			high--;
		 swap(L,low,high);	/* 将比枢轴记录小的记录交换到低端 */
		 while(low<high&&L->r[low]<=pivotkey)
			low++;
		 swap(L,low,high);	/* 将比枢轴记录大的记录交换到高端 */
	}
	return low; 			/* 返回枢轴所在位置 */
}

int pivotkey;

int m = low + (high - low) / 2; 	/* 计算数组中间的元素的下标 */  
if (L->r[low]>L->r[high])			
	swap(L,low,high);				/* 交换左端与右端数据，保证左端较小 */
if (L->r[m]>L->r[high])
	swap(L,high,m);					/* 交换中间与右端数据，保证中间较小 */
if (L->r[m]>L->r[low])
	swap(L,m,low);					/* 交换中间与左端数据，保证左端较小 */

/* 此时L.r[low]已经为整个序列左中右三个关键字的中间值。*/

pivotkey=L->r[low]; 				/* 用子表的第一个记录作枢轴记录 */

/* 快速排序优化算法 */
int Partition1(SqList *L,int low,int high)
{ 
	int pivotkey;

	int m = low + (high - low) / 2; /* 计算数组中间的元素的下标 */  
	if (L->r[low]>L->r[high])			
		swap(L,low,high);			/* 交换左端与右端数据，保证左端较小 */
	if (L->r[m]>L->r[high])
		swap(L,high,m);				/* 交换中间与右端数据，保证中间较小 */
	if (L->r[m]>L->r[low])
		swap(L,m,low);				/* 交换中间与左端数据，保证左端较小 */
	
	pivotkey=L->r[low]; 			/* 用子表的第一个记录作枢轴记录 */
	L->r[0]=pivotkey;  				/* 将枢轴关键字备份到L->r[0] */
	while(low<high) 				/*  从表的两端交替地向中间扫描 */
	{ 
		while(low<high&&L->r[high]>=pivotkey)
			high--;
		L->r[low]=L->r[high];		/* 采用替换而不是交换的方式进行操作 */
		while(low<high&&L->r[low]<=pivotkey)
			low++;
		L->r[high]=L->r[low];		/* 采用替换而不是交换的方式进行操作 */
	}
	L->r[low]=L->r[0];				/* 将枢轴数值替换回L.r[low] */
	return low; 					/* 返回枢轴所在位置 */
}

#define MAX_LENGTH_INSERT_SORT 7 /* 用于快速排序时判断是否选用插入排序阙值 */
/* 对顺序表L中的子序列L.r[low..high]作快速排序 */
void QSort1(SqList *L,int low,int high)
{ 
	int pivot;
	if((high-low)>MAX_LENGTH_INSERT_SORT)
	{
		pivot=Partition1(L,low,high); 	/* 将L->r[low..high]一分为二，算出枢轴值pivot */
		QSort1(L,low,pivot-1);			/* 对低子表递归排序 */
		QSort1(L,pivot+1,high);			/* 对高子表递归排序 */
	}
	else
		InsertSort(L);					/* 当high-low小于等于常数时用直接插入排序 */
}

/* 尾递归 */
void QSort2(SqList *L,int low,int high)
{ 
	int pivot;
	if((high-low)>MAX_LENGTH_INSERT_SORT)
	{
		while(low<high)
		{
			pivot=Partition1(L,low,high); /* 将L->r[low..high]一分为二，算出枢轴值pivot */
			QSort2(L,low,pivot-1);		/* 对低子表递归排序 */
			low=pivot+1;				/* 尾递归 */
		}
	}
	else
		InsertSort(L);					/* 当high-low小于等于常数时用直接插入排序 */
}

