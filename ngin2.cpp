//ngin2.0
#include<cstdio>
#include<cassert>
//cov version2.0 some bugs in it. 
void cov(int* a,int n){
	int i=n-1,j=0;
	while((i>=0)&&(j>=0)){
		while(!a[i]&&(~i)) i--;
		if(i<0) break;
		j=i-1;
		while(!a[j]&&(~j)) j--;
		if(j<0) break;
		if(a[i]==a[j]&&a[j]) a[i]++;
		else a[i-1]=a[j];
		a[j]=0,i--;
	}
}
//cov 2.1 解决了一些问题，增强了稳定性（ 
void cov2(int* a,int n){
	int i=n-1,j=0;
	while(i){
		j=i-1;
		while(!a[j]&&(~j)) --j;
		if(j<0) break;
		if(!a[i]) a[i]=a[j],a[j]=0;
		else{
			if(a[i]==a[j]) a[i]+=1,a[j]=0;
			else if(j!=(i-1)) a[i-1]=a[j],a[j]=0;
			--i;
		}
		for(int k=0;k<n;k++) printf("%d ",a[k]);
		printf("\n");
	}
}
//cov2.2 基于cov2.0改造成二维版本，重构精简了很多代码
//规定-1为空,其余为2^i 
//char direc[4][2]={{0,1},{-1,0},{0,-1},{1,0}}; //0°90°180°270°
//char start[4][2]={{1,0},{1,1},{0,1},{0,0}};
//void cov3(int a[300][300],int size,int dire){
//	dire=(dire+2)&3;
//	int ix,iy;
//	int jx=ix=start[dire][0]*(size-1),
//		jy=iy=start[dire][1]*(size-1);
////	int rec=0;printf("1");
//	while(rec<size){
//		while(1){
//			jx=ix+direc[dire][0],jy=iy+direc[dire][1];
//			while(!a[jx][jy]&&(~jx)&&(~jy)&&(jx<=size)&&(jy<=size)){
//				jx+=direc[dire][0],jy+=direc[dire][1];
////				printf("a %d %d %d %d\n",ix,iy,jx,jy); 
//			}
////			printf("a %d %d %d %d\n",ix,iy,jx,jy); 
//			if((~jx)&&(~jy)&&(jx<size)&&(jy<size)){
//				if(!(a[ix][iy])) a[ix][iy]=a[jx][jy],a[jx][jy]=0;
//				else{
//					if(a[jx][jy]==a[ix][iy]) a[ix][iy]+=1,a[jx][jy]=0;
//					else if(jx!=ix+direc[dire][0]||jy!=iy+direc[dire][1])
//					a[ix+direc[dire][0]][iy+direc[dire][1]]=a[jx][jy],a[jx][jy]=0;
//				}
//				ix+=direc[dire][0],iy+=direc[dire][1];
//			}else break;
////				for(int i=0;i<size;i++){
////					for(int j=0;j<size;j++)
////						printf("%3d",a[i][j]);
////					printf("\n");
////				}
////				printf("\n");
//		}
//		if(direc[(dire+1)&3][0]){
//			ix+=direc[(dire+1)&3][0];
//			iy=start[dire][1]*(size-1);
//		}else{
//			ix=start[dire][0]*(size-1);
//			iy+=direc[(dire+1)&3][1];
//		}
//		rec++;
//	}
//} 
//cov2.3 要求新的方向
char direc[8][2]={{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1}}; //0°45°90°135°180°225°270°315° 
char start[4][2]={{1,0},{1,1},{0,1},{0,0}};
void cov4(int a[300][300],int size,int dire){
	dire=(dire+4)&7;
	int ix,iy;
	int jx=ix=start[dire>>1][0]*(size-1),
		jy=iy=start[dire>>1][1]*(size-1);
	int rec=0;
	while(1){
		while(1){
			jx=ix+direc[dire][0],jy=iy+direc[dire][1];
			printf("a %d %d %d %d\n",ix,iy,jx,jy); 
			while(!a[jx][jy]&&(~jx)&&(~jy)&&(jx<=size)&&(jy<=size)){
				jx+=direc[dire][0],jy+=direc[dire][1];
				printf("a %d %d %d %d\n",ix,iy,jx,jy); 
			}
			printf("a %d %d %d %d\n",ix,iy,jx,jy); 
			if((~jx)&&(~jy)&&(jx<size)&&(jy<size)){
				if(!(a[ix][iy])) a[ix][iy]=a[jx][jy],a[jx][jy]=0;
				else{
					if(a[jx][jy]==a[ix][iy]) a[ix][iy]+=1,a[jx][jy]=0;
					else if(jx!=ix+direc[dire][0]||jy!=iy+direc[dire][1])
					a[ix+direc[dire][0]][iy+direc[dire][1]]=a[jx][jy],a[jx][jy]=0;
				}
				ix+=direc[dire][0],iy+=direc[dire][1];
			}else break;
				for(int i=0;i<size;i++){
					for(int j=0;j<size;j++)
						printf("%3d",a[i][j]);
					printf("\n");
				}
				printf("\n");
		}
		if(!(dire&1)){
			if(direc[(dire+2)&7][0]){
				ix+=direc[(dire+2)&7][0];
				iy=start[dire][1]*(size-1);
			}else{
				ix=start[dire][0]*(size-1);
				iy+=direc[(dire+2)&7][0]; 
			}
		}else{
			if(dire&2){
				if(rec<size){
					iy+=direc[(dire+2)&7][1];
					ix=start[dire>>1][0];
				}else{
					ix+=direc[(dire+2)&7][0];
					iy=start[dire>>1][1];
				}
			}else{
				if(rec<size){
					ix+=direc[(dire+2)&7][0];
					iy=start[dire>>1][1];
				}else{
					ix=start[dire>>1][0];
					iy+=direc[(dire+2)&7][1];
				}
			}
		}
		printf("a %d %d %d %d\n\n",ix,iy,jx,jy);
		rec++;
		if(!(dire&1)&&rec==size) break;
		if((dire&1)&&rec==(2*size-1)) break;
	}
}  
//cov3.0 重新研究新算法，要求有动作（ 
 
//test
int main(){
	int n,all[300][300],m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++) for(int j=0;j<n;j++){
		scanf("%d",&all[i][j]);
	}
	cov4(all,n,m);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++) if(all[i][j]) printf("%3d",1<<all[i][j]);
		else printf("   ");
		printf("\n");
	}
}
