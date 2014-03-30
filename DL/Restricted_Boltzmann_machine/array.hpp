
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

struct t_array
{
	t_array(uint32_t x, uint32_t y,const char* filename):m_X(x),m_Y(y)
	{
		if(filename == NULL)
		{
			m_in = (double*)malloc(x*y*sizeof(double));
			m_fd = -1;
		}
		else
		{
			struct stat sb;
			uint32_t  block_cnt = (x*y*sizeof(double)/1024)+1;
                        if (stat(filename, &sb) == -1) {

                                char command_line[0x100];
                                snprintf(command_line,0x100,"dd if=/dev/zero of=%s bs=1k count=%d",filename,block_cnt);
                                system(command_line);
                        }
                        m_fd = open(filename, O_CREAT|O_RDWR|O_NONBLOCK,00777);
                        m_flen = lseek(m_fd, 1, SEEK_END)-1;
                        m_in = (double*)mmap(0,m_flen,PROT_READ|PROT_WRITE,MAP_SHARED,m_fd,0);
		}
	};
	~t_array()
	{
		if(m_fd == -1)
		{
			free(m_in);
		}
		else
		{
			msync(m_in,m_flen,MS_SYNC);
                        munmap(m_in,m_flen);
                        close(m_fd);
		}
	}
	double* operator[](uint32_t idx)
	{
		//return (T*)((long)(&m_in[idx*m_Y])*(idx<m_X));
		return &m_in[idx*m_Y];
	}
	double* m_in;
	uint32_t m_X;
	uint32_t m_Y;
	int   m_fd;
	off_t m_flen;
};
struct s_array
{
        s_array(uint32_t x,const char* filename):m_X(x)
        {
		if(filename == NULL)
                {
                	m_in = (double*)malloc(x*sizeof(double));
			m_fd = -1;
		}
		else
		{
			struct stat sb;
                        uint32_t  block_cnt = (x*sizeof(double)/1024)+1;
                        if (stat(filename, &sb) == -1) {

                                char command_line[0x100];
                                snprintf(command_line,0x100,"dd if=/dev/zero of=%s bs=1k count=%d",filename,block_cnt);
                                system(command_line);
                        }
                        m_fd = open(filename, O_CREAT|O_RDWR|O_NONBLOCK,00777);
                        m_flen = lseek(m_fd, 1, SEEK_END)-1;
                        m_in = (double*)mmap(0,m_flen,PROT_READ|PROT_WRITE,MAP_SHARED,m_fd,0);
		}

        };
        ~s_array()
        {
		
		if(m_fd == -1)
                {
                        free(m_in);
                }
                else
                {
                        msync(m_in,m_flen,MS_SYNC);
                        munmap(m_in,m_flen);
                        close(m_fd);
                }
        }
        inline double& operator[](uint32_t idx)
        {
		return m_in[idx];
        };
	inline const double operator[](uint32_t idx) const
	{
		return m_in[idx];
	};
        double* m_in;
        uint32_t m_X;
	int   m_fd;
        off_t m_flen;
};
/*
int main(void)
{
	t_array<double> array(4,4);
	
	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;++j)
		{
			printf("%f\t",array[i][j]);
		}
		printf("\n");
	}
}*/
