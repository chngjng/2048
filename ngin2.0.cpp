//cov2.2 基于cov2.0改造成二维版本，重构精简了很多代码
//规定-1为空,其余为2^i 
char direc[4][2]={{0,1},{-1,0},{0,-1},{1,0}}; //0°90°180°270°
char start[4][2]={{1,0},{1,1},{0,1},{0,0}};
void cov3(int a[300][300],int size,int dire){
	dire=(dire+2)&3;
	int ix,iy;
	int jx=ix=start[dire][0]*(size-1),
		jy=iy=start[dire][1]*(size-1);
	int rec=0;
	while(rec<size){
		while(1){
			jx=ix+direc[dire][0],jy=iy+direc[dire][1];
			while(!a[jx][jy]&&(~jx)&&(~jy)&&(jx<=size)&&(jy<=size))
				jx+=direc[dire][0],jy+=direc[dire][1];
			if((~jx)&&(~jy)&&(jx<size)&&(jy<size)){
				if(!(a[ix][iy])) a[ix][iy]=a[jx][jy],a[jx][jy]=0;
				else{
					if(a[jx][jy]==a[ix][iy]) a[ix][iy]+=1,a[jx][jy]=0;
					else if(jx!=ix+direc[dire][0]||jy!=iy+direc[dire][1])
					a[ix+direc[dire][0]][iy+direc[dire][1]]=a[jx][jy],a[jx][jy]=0;
				}
				ix+=direc[dire][0],iy+=direc[dire][1];
			}else break;
		}
		if(direc[(dire+1)&3][0]){
			ix+=direc[(dire+1)&3][0];
			iy=start[dire][1]*(size-1);
		}else{
			ix=start[dire][0]*(size-1);
			iy+=direc[(dire+1)&3][1];
		}
		rec++;
	}
}
