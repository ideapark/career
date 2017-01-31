#include <stdlib.h>
#include <stdio.h>

int main(void)
{
        int people, apples;
        div_t share;
        for (apples = -3; apples < 6; apples += 3) {
                if (apples == 0)
                        continue; /* divided by ZERO */
                for (people = -2; people < 4; people += 2) {
                        if (people == 0)
                                continue; /* divided by ZERO */
                        share = div(apples, people);
                        printf("If there are %+i of us and %+i apples, "
                               "each of us gets %+i, with %+i left over.\n",
                               people, apples, share.quot, share.rem);
                }
        }
        return 0;
}
