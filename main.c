#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
�����ϰ� ���� ū�ʿ��� ���� ������ �ٸ��ʿ� �־��ְ� �ٽ� ũ�⸦ ���ϴ� ����� ��� �ݺ��ϴ� ����̴�.
���� ���̰� 0�� �ȴٸ� �� ��Ȳ�� ���� ���� �� ���� ���� �ִ�Ƚ���� �Ѿ�� �� �̻� ����� ���� �����Ƿ� 
��찡 ������ �ʴ´�.
�ִ� Ƚ���� ����Ʈ 1,2�� ���� �� + ���� ū ����Ʈ ���� -3�ε� �� ���� ���� 1���� ������ ������ �հ� ���� ���̴�.
���� �� ū ���ڰ� �� �������� 1ĭ �տ� �ִٰ� ���� �׷��� �츮�� �� ū�� 1���� ���ܾ� �ϹǷ� �տ� �ִ� ��� ���� ū ���� 
�ٸ� ����Ʈ�� �Űܾ��Ѵ�.(���� ū ����Ʈ ���� - 1��ŭ ����) ���� �ٸ� ����Ʈ���� ū ���� ���� �� ���� ū �� ���� ��� ����
�̵������־�� �Ѵ�.(���� ū ����Ʈ ���� - 2 + �ٸ� ����Ʈ ����) �׷��� ���������� �ִ�
����Ʈ 1,2�� ���� �� + ���� ū ����Ʈ ���� -3��ŭ�� ������ �ϰ� �ȴ�.
*/

// queue1_len�� �迭 queue1�� �����Դϴ�.
// queue2_len�� �迭 queue2�� �����Դϴ�.

#define LOGPRINT 0

void CopyList(int list[], int length, int copylist[])
// ����Ʈ�� ī���ϴ� �Լ�
{
    for (int i = 0; i < length; i++)
    {
        copylist[i] = list[i];
    }
}

int ListSum(int list[], size_t ListLen)
// ����Ʈ ������ �� ���� ���ϴ� �Լ�
{
    int sum = 0;

    for (int index = 0; index < ListLen; index++)
    {
        sum += list[index];
    }

    return sum;
}

int solution(int queue1[], size_t queue1_len, int queue2[], size_t queue2_len) {
    unsigned int List1Sum = ListSum(queue1, queue1_len);
    unsigned int List2Sum = ListSum(queue2, queue2_len);
    unsigned int ListTotalSum = List1Sum + List2Sum;
    // ����Ʈ�� �� ���� ������ ����
    int LongLength = 0;
    int popnum = 0;
    // �շ����� ��ȯ Ƚ���� ���ϱ� ���� ����
    // �� ���� ����Ʈ�� ���� ���� ���ڸ� ��� ����
    if (List1Sum > List2Sum)
    {
        LongLength = queue1_len;
    }
    else
    {
        LongLength = queue2_len;
    }
    // �ִ� ��ȯ Ƚ���� ����Ʈ 1,2�� ���� �� + ���� ū ����Ʈ ���� -3�� �ִ� ��ȯ Ƚ���̴�.

    int* list1 = malloc(sizeof(int) * (queue1_len + queue2_len + LongLength));
    int* list2 = malloc(sizeof(int) * (queue1_len + queue2_len + LongLength));

    CopyList(queue1, queue1_len, list1);
    CopyList(queue2, queue2_len, list2);
    // �Ű������� �޾ƿ� ����Ʈ�� �ٷ�� ���� ���� �Ҵ����� ī���Ͽ���.
    if (ListTotalSum % 2 == 1)
        // �� ���� Ȧ���� �翬�� �� ����Ʈ�� ���� ���� �� ����.
    {
        printf("���� Ȧ��\n");
        return -1;
    }

    unsigned int List1Start = 0;
    unsigned int List1End = queue1_len;
    unsigned int List2Start = 0;
    unsigned int List2End = queue2_len;
    // pop�Լ��� insert�Լ��� ���ְ� �׿� ������ �ൿ�� �� �� �ְ� �ϴ� ������ ����
    for (int count = 0; count < queue1_len + queue2_len + LongLength - 2; count++)
    {
        if (List1Sum > List2Sum)
        {
            popnum = list1[List1Start];
            list2[List2End] = popnum;
            List1Sum -= popnum;
            List2Sum += popnum;
            List1Start += 1;
            List2End += 1;
        }
        else if (List1Sum < List2Sum)
        {
            popnum = list2[List2Start];
            list1[List1End] = popnum;
            List1Sum += popnum;
            List2Sum -= popnum;
            List2Start += 1;
            List1End += 1;
        }
        else if (List1Sum == List2Sum)
        {
            return count;
        }

        if (queue1_len == 0 || queue2_len == 0)
        {
            printf("���� �迭�� ���̰� 0�� �Ǿ���");
            return -1;
        }

        if (LOGPRINT)
        {
            printf("\nlist1 : ");
            for (int i = 0; i < queue1_len; i++)
            {
                printf("%d ", list1[i]);
            }
            printf("\nlist2 : ");
            for (int i = 0; i < queue2_len; i++)
            {
                printf("%d ", list2[i]);
            }
            printf("\n");
        }
    }
    printf("������ ������ ����\n");

    return -1;
}

int main()
{
    int queue1[6] = { 2,4,2,2,3,1 };
    int queue2[3] = { 1,16,1 };

    int answer = solution(queue1, 6, queue2, 3);
    printf("%d", answer);

}