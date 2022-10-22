#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
간단하게 합이 큰쪽에서 수를 뺀다음 다른쪽에 넣어주고 다시 크기를 비교하는 방법을 계속 반복하는 방식이다.
한쪽 길이가 0이 된다면 그 상황은 합이 같을 수 없고 또한 최대횟수를 넘어가면 더 이상 경우의 수가 없으므로 
경우가 나오지 않는다.
최대 횟수는 리스트 1,2의 길이 합 + 합이 큰 리스트 길이 -3인데 그 경우는 숫자 1개가 나머지 수들의 합과 같을 때이다.
예로 그 큰 숫자가 맨 마지막에 1칸 앞에 있다고 하자 그러면 우리는 그 큰수 1개만 남겨야 하므로 앞에 있는 모든 수와 큰 수를 
다른 리스트로 옮겨야한다.(합이 큰 리스트 길이 - 1만큼 수행) 이후 다른 리스트에서 큰 수만 남을 때 까지 큰 수 앞의 모든 수를
이동시켜주어야 한다.(합이 큰 리스트 길이 - 2 + 다른 리스트 길이) 그래서 최종적으로 최대
리스트 1,2의 길이 합 + 합이 큰 리스트 길이 -3만큼의 수행을 하게 된다.
*/

// queue1_len은 배열 queue1의 길이입니다.
// queue2_len은 배열 queue2의 길이입니다.

#define LOGPRINT 0

void CopyList(int list[], int length, int copylist[])
// 리스트를 카피하는 함수
{
    for (int i = 0; i < length; i++)
    {
        copylist[i] = list[i];
    }
}

int ListSum(int list[], size_t ListLen)
// 리스트 인자의 총 합을 구하는 함수
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
    // 리스트의 총 합을 변수에 담음
    int LongLength = 0;
    int popnum = 0;
    // 롱렌쓰는 순환 횟수를 구하기 위한 변수
    // 팝 넘은 리스트의 제일 앞의 숫자를 담는 변수
    if (List1Sum > List2Sum)
    {
        LongLength = queue1_len;
    }
    else
    {
        LongLength = queue2_len;
    }
    // 최대 순환 횟수는 리스트 1,2의 길이 합 + 합이 큰 리스트 길이 -3이 최대 순환 횟수이다.

    int* list1 = malloc(sizeof(int) * (queue1_len + queue2_len + LongLength));
    int* list2 = malloc(sizeof(int) * (queue1_len + queue2_len + LongLength));

    CopyList(queue1, queue1_len, list1);
    CopyList(queue2, queue2_len, list2);
    // 매개변수로 받아온 리스트를 다루기 쉽게 동적 할당으로 카피하였다.
    if (ListTotalSum % 2 == 1)
        // 총 합이 홀수면 당연히 두 리스트의 합이 같을 수 없다.
    {
        printf("합이 홀수\n");
        return -1;
    }

    unsigned int List1Start = 0;
    unsigned int List1End = queue1_len;
    unsigned int List2Start = 0;
    unsigned int List2End = queue2_len;
    // pop함수와 insert함수를 없애고 그와 유사한 행동을 할 수 있게 하는 변수를 도입
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
            printf("한쪽 배열의 길이가 0이 되었음");
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
    printf("조합이 나오지 않음\n");

    return -1;
}

int main()
{
    int queue1[6] = { 2,4,2,2,3,1 };
    int queue2[3] = { 1,16,1 };

    int answer = solution(queue1, 6, queue2, 3);
    printf("%d", answer);

}