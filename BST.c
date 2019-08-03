#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct interval{
	int lo,hi;
} Interval;

typedef struct Node{
	Interval* Inter;
	
	int max;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
} node;

void make_node(node* z,Interval* i){
	z->Inter=(Interval*)malloc(1*sizeof(Interval));
 	z->Inter->lo=i->lo;
	z->Inter->hi=i->hi;
	z->max=i->hi;
	z->left=NULL;
	z->right=NULL;
	z->parent=NULL;
}

node* Insert1(node* root,Interval* i){
 	node* z;
 	z=(node*)malloc(1*sizeof(node));
 	
    make_node(z,i); //z is to be inserted
	node* y=NULL;
	node* x=root;
	while(x!=NULL){
		y=x;
		if(z->Inter->lo < x->Inter->lo){
			if(y->max < i->hi)
				y->max=i->hi;
			x=x->left;
		}
		else {
			if(y->max < i->hi)
				y->max=i->hi;
			x=x->right;
		}
	}

	z->parent=y;
	if(y==NULL)
		root=z;
	else if(z->Inter->lo < y->Inter->lo)
		y->left=z;
	else y->right=z;

	return root;
	
}

node* Insert2(node* root,Interval* i){
	node* z;
 	z=(node*)malloc(1*sizeof(node));
 	
    make_node(z,i); //z is to be inserted
	node* y=NULL;
	node* x=root;
	while(x!=NULL){
		y=x;
		if(z->Inter->hi < x->Inter->hi){
			if(y->max < i->hi)
				y->max=i->hi;
			x=x->left;
		}
		else {
			if(y->max < i->hi)
				y->max=i->hi;
			x=x->right;
		}
	}

	z->parent=y;
	if(y==NULL)
		root=z;
	else if(z->Inter->hi < y->Inter->hi)
		y->left=z;
	else y->right=z;

	return root;
	
}
node* transplant(node* root,node* u,node* v){
	if(u==root)
		root=v;
	else{
	    	if(u==u->parent->left)
	    		u->parent->left=v;
	    	else 
	    	    u->parent->right=v;
	}
	if(v!=NULL)
    		v->parent=u->parent;
	return root;
}

Interval* Min(node* root){
	if(root==NULL)
		return NULL;
	else{
		while(root->left!=NULL){
			root=root->left;
		}
		return root->Inter;
	}
}

Interval* Max(node* root){

	if(root==NULL)
		return NULL;
	else{
		while(root->right!=NULL){
			root=root->right;
		}
		return root->Inter;
	}
}

node* Search(node* root,Interval* i){
	if(root==NULL)
		return NULL;
	else if((root->Inter->lo==i->lo)&&(root->Inter->hi==i->hi))
		return root;
	else if(i->lo < root->Inter->lo)
		return Search(root->left,i);
	else
		return Search(root->right,i);
}

node* Search2(node* root,Interval* i){
	if(root==NULL)
		return NULL;
	else if((root->Inter->lo==i->lo)&&(root->Inter->hi==i->hi))
		return root;
	else if(i->hi < root->Inter->hi)
		return Search(root->left,i);
	else
		return Search(root->right,i);
}
node* Search_hi(node* root,Interval* i){
    if(root==NULL)
        return NULL;
    else if(root->Inter->hi==i->hi)
        return root;
    else if(root->Inter->hi<i->hi)
        Search_hi(root->right,i);
    else Search_hi(root->left,i);
}
node* Search_lo(node* root,Interval* i){
    if(root==NULL)
        return NULL;
    else if(root->Inter->lo==i->lo)
        return root;
    else if(root->Inter->lo<i->lo)
        Search_lo(root->right,i);
    else Search_lo(root->left,i);
}
node* Tree_Min(node* root){
	if(root!=NULL){
		while(root->left!=NULL)
			root=root->left;
	}
	return root;
}
Interval* Tree_Min2(node* root){
	if(root!=NULL){
		while(root->left!=NULL)
			root=root->left;
	}
	return root->Inter;
}

// int find_max(node*a,node*b,node*c){
// 	int p,q,r;
// 	if(a==NULL){

// 	}
// }

int maximum_2(int a,int b){
	if(a>b)
		return a;
	return b;
}
int maximum_3(int a,int b,int c){
	return maximum_2(maximum_2(a,b),c);
}
void Max_Update(node*root,node*y){
	//printf("%d",y->Inter->lo);
	if(y==NULL)	
		return;
	else{
		if(y->left==NULL&&y->right==NULL){
			y->max=y->Inter->hi;
		}
		else if(y->left==NULL){
			y->max=maximum_2(y->right->max,y->Inter->hi);
		}
		else if(y->right==NULL){
			y->max=maximum_2(y->left->max,y->Inter->hi);
		}
		else{
			y->max=maximum_3(y->left->max,y->Inter->hi,y->right->max);
		}
		if(y!=y->parent)   
		    Max_Update(root,y->parent);
	}
}
node* Delete(node* root,Interval* i){
	node* z=Search(root,i);
	node*y;
	if(z!=NULL){
	    	if(z->left==NULL){
	    		y=z->right;
	    		root=transplant(root,z,z->right);
	  	}
	    	else if(z->right==NULL){
	    		y=z->left;
	    		root=transplant(root,z,z->left);
	    	}
	    	else{
	    		y=Tree_Min(z->right);
	    		if(y->parent!=z){
	    			root=transplant(root,y,y->right);
	    			y->right=z->right;
	    			y->right->parent=y;
	    		}
	    		root=transplant(root,z,y);
	    		y->left=z->left;
	    		y->left->parent=y;
	    	}
	    	Max_Update(root,y);
	    	
	}

	return root;
}

node* Delete2(node* root,Interval* i){

	node* z=Search2(root,i);
	node*y;
	if(z!=NULL){
	    	if(z->left==NULL){
	    		y=z->right;
	    		root=transplant(root,z,z->right);
	  	}
	    	else if(z->right==NULL){
	    		y=z->left;
	    		root=transplant(root,z,z->left);
	    	}
	    	else{
	    		y=Tree_Min(z->right);
	    		if(y->parent!=z){
	    			root=transplant(root,y,y->right);
	    			y->right=z->right;
	    			y->right->parent=y;
	    		}
	    		root=transplant(root,z,y);
	    		y->left=z->left;
	    		y->left->parent=y;
	    	}
	    	Max_Update(root,y);
	}

	return root;

	// node* z=Search2(root,i);
	// if(z!=NULL){
 //    	if(z->left==NULL)
 //    		root=transplant(root,z,z->right);
 //    	else if(z->right==NULL)
 //    		root=transplant(root,z,z->left);
 //    	else{
 //    		node* y=Tree_Min(z->right);
 //    		if(y->parent!=z){
 //    			root=transplant(root,y,y->right);
 //    			y->right=z->right;
 //    			y->right->parent=y;
 //    		}
 //    		root=transplant(root,z,y);
 //    		y->left=z->left;
 //    		y->left->parent=y;
 //    	}
	// }

	// return root;
}

Interval* LoSucc(node* root,Interval* i){
	node*y;
	node* z=Search_lo(root,i);
	if(root==NULL)
		return NULL;
    if(z==NULL)
        return NULL;
	else if(z->right!=NULL){
	    return Tree_Min2(z->right);
	}
	else if(z==root)
	    return NULL;
	else{
	    y=z->parent;
	    while(y!=NULL&&z==y->right){
	        z=y;
	        y=y->parent;
	    }
	    if(y==NULL)
	        return NULL;
	    else
	        return y->Inter;
	}
	    
	
}



Interval* HiSucc(node* root,Interval* i){
	node*y;
	node* z=Search_hi(root,i);
	if(root==NULL)
		return NULL;
    if(z==NULL)
        return NULL;
	else if(z->right!=NULL){
	    return Tree_Min2(z->right);
	}
	// else if(z==root)
	//     return NULL;
	else{
	    y=z->parent;
	    while(y!=NULL&&z==y->right){
	        z=y;
	        y=y->parent;
	    }
	    if(y==NULL)
	        return NULL;
	    else
	        return y->Inter;
	}
}

int IntOverlap(Interval* a, Interval* b){
	if(a->lo <= b->hi && b->lo <= a->hi)
		return 1;
	return 0;
}
int IsOverlap(node* root, Interval* i){
	node* y=root;
	if(y==NULL)
		return 0;
	else if(IntOverlap((y->Inter),i))
		return 1;
	else if(y->left!=NULL && y->left->max >= i->lo)
		return IsOverlap(y->left,i);
	return IsOverlap(y->right,i);
}

int main() {
	int m;
	scanf("%d",&m);
	while(m--){
		int n;
		scanf("%d",&n);
		node* root1=NULL;
		node* root2=NULL;
		while(n--){
			char* str;
			str=(char*)malloc(10*sizeof(char));
			scanf("%s",str);
			if(!strcmp(str,"+")){
				int l,h;
				scanf("%d%d",&l,&h);
				//printf("%d %d",l,h);
				Interval* i;
				i=(Interval*)malloc(1*sizeof(Interval));
				i->lo=l;
				i->hi=h;
				//printf("%d%d",i->lo,i->hi);
				root1=Insert1(root1,i);
				root2= Insert2(root2,i);
			}
			else if(!strcmp(str,"-")){
				int l,h;
				scanf("%d%d",&l,&h);
				Interval* i;
				i=(Interval*)malloc(1*sizeof(Interval));
				i->lo=l;
				i->hi=h;
				node*z;
				root1=Delete(root1,i);
				root2=Delete2(root2,i);
				//printf("(%d %d)",z->Inter->lo,z->Inter->hi);
				root1=Delete(root1,i);
				root2=Delete2(root2,i);
			}
			else if(!strcmp(str,"min")){
				Interval* i;
				i=Min(root1);
				printf("[%d %d]\n",i->lo,i->hi);
			}
			else if(!strcmp(str,"max")){
				Interval* i;
				i=Max(root2);
				printf("[%d %d]\n",i->lo,i->hi);
			}
			else if(!strcmp(str,"lsucc")){
				Interval* i;
				i=(Interval*)malloc(1*sizeof(Interval));
				Interval* f;
				f=(Interval*)malloc(1*sizeof(Interval));
				int l,h;
				scanf("%d%d",&l,&h);
				i->lo=l;
				i->hi=h;
				f=LoSucc(root1,i);
				if(f==NULL)
				    printf("INVALID\n");
				else
				    printf("[%d %d]\n",f->lo,f->hi);
			}
			else if(!strcmp(str,"hsucc")){
				Interval* i;
				i=(Interval*)malloc(1*sizeof(Interval));
				Interval* f;
				f=(Interval*)malloc(1*sizeof(Interval));
				int l,h;
				scanf("%d%d",&l,&h);
				i->lo=l;
				i->hi=h;
				f=HiSucc(root2,i);
				if(f==NULL)
				    printf("INVALID\n");
				else
				    printf("[%d %d]\n",f->lo,f->hi);
			}
			else if(!strcmp(str,"overlap")){
				Interval* i;
				i=(Interval*)malloc(1*sizeof(Interval));
				int l,h;
				scanf("%d%d",&l,&h);
				i->lo=l;
				i->hi=h;
				printf("%d\n",IsOverlap(root1,i));
			}
		}
		
	}
	return 0;
}