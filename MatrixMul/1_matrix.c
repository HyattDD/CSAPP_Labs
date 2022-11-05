#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<memory.h>
 
/*定义矩阵中元素的上限，避免相乘后溢出*/
#define RANGE 10
/*矩阵A有M行N列，矩阵B有N行M列*/
#define M 500
#define N 800

void gene_matrix();
void read_matrix();
void write_matrix();

int matrixA[M][N];
int matrixB[N][M];

int main()
{
    gene_matrix();                                      //用随机数产生两个待相乘的矩阵，并分别存入两个文件中
    read_matrix();                                      //从两个文件中读出数据赋给matrixA和matrixB
    clock_t start=clock();                              //开始计时
    int res[M][M]={0};                                  //保存矩阵相乘的结果。非全局变量一定要显示初始化为0,否则为随机的一个数
    int i,j,k;
    for(i=0;i<M;i++)                                 
        for(j=0;j<M;j++)
            for(k=0;k<N;k++)
                res[i][j]+=matrixA[i][k]*matrixB[k][j];   
    write_matrix(res);
    clock_t finish=clock();                             //结束计算
    printf("串行计算用时%.2f秒\n",(long)(finish-start)/1E6);
    return 0;
}

void gene_matrix()
{
    FILE *file1,*file2;
    if((file1=fopen("matrixA.txt","wt"))==NULL)
    {
        perror("fopen");
        exit(1);
    }
    if((file2=fopen("matrixB.txt","wt"))==NULL)
    {
        perror("fopen");
        exit(1);
    }
    int i,j;
    srand((unsigned)time(NULL));
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
            fprintf(file1,"%-8d",rand()%RANGE);
        fprintf(file1,"\n");
    }
    fclose(file1);
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
            fprintf(file2,"%-8d",rand()%RANGE);
        fprintf(file2,"\n");
    }
    fclose(file2);  
}
 
void read_matrix()
{
    FILE *file1,*file2;
    if((file1=fopen("matrixA.txt","rt"))==NULL)
    {
        perror("fopen");
        exit(1);
    }
    if((file2=fopen("matrixB.txt","rt"))==NULL)
    {
        perror("fopen");
        exit(1);
    }
    int i,j;
    for(i=0;i<M;i++)
        for(j=0;j<N;j++)
            fscanf(file1,"%d",&matrixA[i][j]);
    fclose(file1);
    for(i=0;i<N;i++)
        for(j=0;j<M;j++)
            fscanf(file2,"%d",&matrixB[i][j]);
    fclose(file2);
}

void write_matrix(int const *matrix) {
    FILE *file;
    if((file=fopen("matrixC.txt","wt"))==NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    int i,j;
    for(i=0;i<M;i++)
    {
        for(j=0;j<M;j++)
            fprintf(file,"%-8d",matrix[i*M+j]);
        fprintf(file,"\n");
    }
    fclose(file);
}