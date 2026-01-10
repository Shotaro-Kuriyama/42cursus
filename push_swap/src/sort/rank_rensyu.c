
//#include "push_swap.h"


//void rank(t_stack *a)
//{
//	t_node *cur;
//	t_node *search;
	
//	if (a->size == 0 || a->size == 1)
//		return;

//	cur = a->sentinel.next;
//	while (cur != &a->sentinel)
//	{
//		cur->rank = 0;
//		search = a->sentinel.next;
//		while (search != &a->sentinel)
//		{
//			if (cur->value > search->value)
//				cur->rank++;
//			search = search->next;
//		}
//		cur = cur->next;
//	}
//}


//// マージソート＋二分探索で「座標圧縮」をする考え方

////まずは、マージソートを実装するが、マージソートは「配列」を扱う
////のが基本なので、まず部品Aから作る。
////部品A：スタック → 配列に値をコピーする
//static void coppied(t_stack *a,  int *values)
//{
//	t_node *cur;

//	size_t i;
//	cur = a->sentinel.next;
//	while (cur != &a->sentinel)
//	{
//		values[i] = cur->value;
//		i++;
//		cur = cur->next;
//	}
//}

//static void marge_sort()
//{
	
//}



//bool rank_marge(t_stack *a)
//{
//	size_t n;
//	int *values;
//	n = a->size;

//	values = (int *)malloc(sizeof(int) * n); //要素数分の配列を確保
//	coppied(a, values);
//}




