#include "string.h"
#include "stdlib.h"


#define FILE_MAX_TYPE_NUM		7	//���FILE_MAX_TYPE_NUM������
#define FILE_MAX_SUBT_NUM		4	//���FILE_MAX_SUBT_NUM��С��

 //�ļ������б�
u8*const FILE_TYPE_TBL[FILE_MAX_TYPE_NUM][FILE_MAX_SUBT_NUM]=
{
{"BIN"},			//BIN�ļ�
{"LRC"},			//LRC�ļ�
{"NES","SMS"},		//NES/SMS�ļ�
{"TXT","C","H"},	//�ı��ļ�
{"WAV","MP3","APE","FLAC"},//֧�ֵ������ļ�
{"BMP","JPG","JPEG","GIF"},//ͼƬ�ļ�
{"AVI"},			//��Ƶ�ļ�
};
///////////////////////////////�����ļ���,ʹ��malloc��ʱ��////////////////////////////////////////////
FATFS *fs[_VOLUMES];//�߼����̹�����.	 
FIL *file;	  		//�ļ�1
FIL *ftemp;	  		//�ļ�2.
UINT br,bw;			//��д����
FILINFO fileinfo;	//�ļ���Ϣ
DIR dir;  			//Ŀ¼

u8 *fatbuf;			//SD�����ݻ�����


//��Сд��ĸתΪ��д��ĸ,���������,�򱣳ֲ���.
u8 char_upper(u8 c)
{
	if(c<'A')return c;//����,���ֲ���.
	if(c>='a')return c-0x20;//��Ϊ��д.
	else return c;//��д,���ֲ���
}	      
//�����ļ�������
//fname:�ļ���
//����ֵ:0XFF,��ʾ�޷�ʶ����ļ����ͱ��.
//		 ����,����λ��ʾ��������,����λ��ʾ����С��.
u8 f_typetell(u8 *fname)
{
	u8 tbuf[5];
	u8 *attr='\0';//��׺��
	u8 i=0,j;
	while(i<250)
	{
		i++;
		if(*fname=='\0')break;//ƫ�Ƶ��������.
		fname++;
	}
	if(i==250)return 0XFF;//������ַ���.
 	for(i=0;i<5;i++)//�õ���׺��
	{
		fname--;
		if(*fname=='.')
		{
			fname++;
			attr=fname;
			break;
		}
  	}
	strcpy((char *)tbuf,(const char*)attr);//copy
 	for(i=0;i<4;i++)tbuf[i]=char_upper(tbuf[i]);//ȫ����Ϊ��д 
	for(i=0;i<FILE_MAX_TYPE_NUM;i++)	//����Ա�
	{
		for(j=0;j<FILE_MAX_SUBT_NUM;j++)//����Ա�
		{
			if(*FILE_TYPE_TBL[i][j]==0)break;//�����Ѿ�û�пɶԱȵĳ�Ա��.
			if(strcmp((const char *)FILE_TYPE_TBL[i][j],(const char *)tbuf)==0)//�ҵ���
			{
				return (i<<4)|j;
			}
		}
	}
	return 0XFF;//û�ҵ�		 			   
}	 

//�õ�����ʣ������
//drv:���̱��("0:"/"1:")
//total:������	 ����λKB��
//free:ʣ������	 ����λKB��
//����ֵ:0,����.����,�������
u8 exf_getfree(u8 *drv,u32 *total,u32 *free)
{
	FATFS *fs1;
	u8 res;
    u32 fre_clust=0, fre_sect=0, tot_sect=0;
    //�õ�������Ϣ�����д�����
    res =(u32)f_getfree((const TCHAR*)drv, (DWORD*)&fre_clust, &fs1);
    if(res==0)
	{											   
	    tot_sect=(fs1->n_fatent-2)*fs1->csize;	//�õ���������
	    fre_sect=fre_clust*fs1->csize;			//�õ�����������	   
#if _MAX_SS!=512				  				//������С����512�ֽ�,��ת��Ϊ512�ֽ�
		tot_sect*=fs1->ssize/512;
		fre_sect*=fs1->ssize/512;
#endif	  
		*total=tot_sect>>1;	//��λΪKB
		*free=fre_sect>>1;	//��λΪKB 
 	}
	return res;
}		   

//�õ�·���µ��ļ���
//����ֵ:0,·�����Ǹ�����.
//    ����,�ļ��������׵�ַ
u8* exf_get_src_dname(u8* dpfn)
{
	u16 temp=0;
 	while(*dpfn!=0)
	{
		dpfn++;
		temp++;	
	}
	if(temp<4)return 0; 
	while((*dpfn!=0x5c)&&(*dpfn!=0x2f))dpfn--;	//׷����������һ��"\"����"/"�� 
	return ++dpfn;
}
//�õ��ļ��д�С
//ע���ļ��д�С��Ҫ����4GB.
//����ֵ:0,�ļ��д�СΪ0,���߶�ȡ�����з����˴���.
//    ����,�ļ��д�С.
u32 exf_fdsize(u8 *fdname)
{
#define MAX_PATHNAME_DEPTH	512+1	//���Ŀ���ļ�·��+�ļ������
	u8 res=0;	  
    DIR *fddir=0;		//Ŀ¼
	FILINFO *finfo=0;	//�ļ���Ϣ
	u8 * pathname=0;	//Ŀ���ļ���·��+�ļ���
 	u16 pathlen=0;		//Ŀ��·������
	u32 fdsize=0;

	fddir=(DIR*)malloc(sizeof(DIR));//�����ڴ�
 	finfo=(FILINFO*)malloc(sizeof(FILINFO));
   	if(fddir==NULL||finfo==NULL)res=100;
	if(res==0)
	{ 
 		pathname=(u8*)malloc(MAX_PATHNAME_DEPTH);	    
 		if(pathname==NULL)res=101;	   
 		if(res==0)
		{
			pathname[0]=0;	    
			strcat((char*)pathname,(const char*)fdname); //����·��	
		    res=f_opendir(fddir,(const TCHAR*)fdname); 		//��ԴĿ¼
		    if(res==0)//��Ŀ¼�ɹ� 
			{														   
				while(res==0)//��ʼ�����ļ�������Ķ���
				{
			        res=f_readdir(fddir,finfo);						//��ȡĿ¼�µ�һ���ļ�
			        if(res!=FR_OK||finfo->fname[0]==0)break;		//������/��ĩβ��,�˳�
			        if(finfo->fname[0]=='.')continue;     			//�����ϼ�Ŀ¼
					if(finfo->fattrib&0X10)//����Ŀ¼(�ļ�����,0X20,�鵵�ļ�;0X10,��Ŀ¼;)
					{
 						pathlen=strlen((const char*)pathname);		//�õ���ǰ·���ĳ���
						strcat((char*)pathname,(const char*)"/");	//��б��
						strcat((char*)pathname,(const char*)finfo->fname);	//Դ·��������Ŀ¼����
 						//printf("\r\nsub folder:%s\r\n",pathname);	//��ӡ��Ŀ¼��
						fdsize+=exf_fdsize(pathname);				//�õ���Ŀ¼��С,�ݹ����
						pathname[pathlen]=0;						//���������
					}else fdsize+=finfo->fsize;						//��Ŀ¼,ֱ�Ӽ����ļ��Ĵ�С
						
				} 
		    }	  
  			free(pathname);	     
		}
 	}
	free(fddir);    
	free(finfo);
	if(res)return 0;
	else return fdsize;
}	  







