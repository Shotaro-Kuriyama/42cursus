
#include <fcntl.h>   // open, O_* フラグ
#include <unistd.h>  // read, write, close
#include <stdio.h>   // perror





int main(void)
{
	int fd = open("test.txt", O_RDONLY);//読み取り専用
	if (fd < 0)
	{
		perror("open");
		return 1;
	}

	char buf[100]; //読み取り用の一時バッファ
	ssize_t n;

	n = read(fd, buf, sizeof buf); // sizeof buf = ファイルから読み込むバイト数
	if(n < 0)
	{
		perror("read");
		close(fd);
		return 1;
	}


	write(1, buf, n);
	close(fd);
	return 0;

}