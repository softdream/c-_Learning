//���ֱ�����̰���㷨
#include<stdio.h>

int main()
{
	int n, i, j;//������n����Ʒ
	double c, value; //����һ�������ܹ����ص���������c,����ֵ��value
	double w[20], v[20];//�����i����Ʒ��������w[i],��ֵ��v[i]
	double p[20], x[20], temp, k;//�����i����Ʒ�ĵ�λ��ֵ��p[i],��ѡ�еı�����x[i]


	for (i = 0; i<20; i++) {
		w[i] = 0; v[i] = 0; p[i] = 0; x[i] = 0;
	}//�����ʼ��

	printf("��������Ʒ�������ͱ����ĳ������������ͳ������ö��ŷֿ�����\n");
	scanf_s("%d,%lf", &n, &c);
	if (n <= 0 || c <= 0) {
		printf("������������");
		return 0;
	}


	printf("����������ÿ����Ʒ�������ͼ�ֵ�������ͼ�ֵ�ö��ŷֿ�����\n");
	for (i = 1; i <= n; i++) {
		scanf_s("%lf,%lf", &w[i], &v[i]);
		if (w[i] <= 0 || v[i] <= 0) {
			printf("������������");
			return 0;
		}
		p[i] = v[i] / w[i];//�õ���Ʒ�ĵ�λ��ֵ
	}


	for (i = 1; i<n; i++)//�Ӵ�Сð������
		for (j = i + 1; j <= n; j++)
			if (p[i]<p[j]) {
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;

				temp = w[i];
				w[i] = w[j];
				w[j] = temp;

				temp = v[i];
				v[i] = v[j];
				v[j] = temp;
			}


	i = 1; k = c; value = 0;
	while (i <= n&&k>0)//����ѡ��λ��ֵ�����Ʒ��ֱ������װ��
	{
		if (k >= w[i])//��װ��һ������Ʒ
		{
			x[i] = 1;
			value = value + v[i];
			k = k - w[i];
			i++;
		}

		else {
			x[i] = k / w[i];//ֻ��װ��һ������Ʒ
			value = value + x[i] * v[i];
			break;
		}
	}

	printf("\n����ֵ��:%.2lf \n", value);//�������ֵ

	printf("��ѡ�е���Ʒ�У�\n");
	for (i = 1; i <= n; i++)
		if (x[i]>0)
			printf("����Ϊ%.2lf,��ֵΪ%.2lf����Ʒ,����Ϊ%.4lf%;\n", w[i], v[i], x[i]); //�����ѡ�е���Ʒ
}