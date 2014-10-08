#include <R.h>
#include <Rinternals.h>

static int iii;


void net_reorder(int node, int n, int *e1, int *e2, int *neworder, int *L, int *pos1, int *pos2)
{   
    node = node;
    int i = pos1[node], j, k;
    for (j = 0; j < pos2[node]; j++) {
        k = L[i + j];
		neworder[iii++] = k + 1;
		if (e2[k] > n) /* is it an internal edge? */
			net_reorder(e2[k], n, e1, e2, neworder, L, pos1, pos2);
	}
}

/*
void foo_reorder_ape(int node, int n, int m, int *e1, int *e2, int *neworder, int *L, int *pos)
{
    int i = node - n - 1, j, k;

// 'i' is the C index corresponding to 'node' 

	for (j = 0; j < pos[i]; j++) {
		k = L[i + m * j];
		neworder[iii++] = k + 1;
		if (e2[k] > n) 
			foo_reorder(e2[k], n, m, e1, e2, neworder, L, pos);
	}
}
*/

void order_networx(int *ntips, int *nEdges, int *mNodes, int *e1, int *e2, int *root, int * neworder){
    int i, j, m = mNodes[0]+1L;//m=*mNodes - *ntips;
    int *pos1, *pos2, *tmp, *L; 
    tmp = (int*)R_alloc(m, sizeof(int));
    pos1 = (int*)R_alloc(m, sizeof(int));
    pos2 = (int*)R_alloc(m, sizeof(int));
    L = (int*)R_alloc(*nEdges, sizeof(int));
    for(i = 0; i<m; i++) tmp[i]=0; 
    for(i = 0; i<m; i++) pos1[i]=0; 
    for(i = 0; i<m; i++) pos2[i]=0;

    for(i = 0; i<*nEdges; i++) tmp[e1[i]]++;
  // pos1[0]=0;
    for(i = 0; i<(*mNodes); i++) pos1[i+1]=pos1[i] + tmp[i];
     for(i = 0; i<*nEdges; i++){
         j = e1[i];
         L[pos1[j] + pos2[j]] = i;  
         pos2[j]++;
    }
    net_reorder(*root, *ntips, e1, e2, neworder, L, pos1, tmp);

//   for(i = 0; i<*nEdges; i++) neworder[i] = L[i];
}




