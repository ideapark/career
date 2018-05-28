-- Author: Rong Jian <jian.rong@dmall.com>
-- Review: Zhou Peng <peng.zhou@dmall.com>

-- 没有被清洗
SELECT
	sku,
	werks,
	promo_label
FROM
	clean_order
WHERE
	dt = 20180502 AND
  clean_flag = 'ALL_PASSED'
LIMIT 10;

-- 该店该品最近半年销量中位数 设为Z
-- clean_order.promo_label=0,则type=normal,
-- clean_order.promo_label=1,则type=prom
SELECT
	qty_median
FROM
	preprocess_sixmonth
WHERE
	dt = 20180502 AND
  sku = 104436 AND
  werks = 1166 AND
  type = 'normal';

-- 该店该品当日小票数量top2
-- 第一行salequantityde/第二行salequantityde 即为该店该品当日小票最大值No.1/该店该品当日小票第二大值No.2设为Y
-- 预期
--	只有一条记录
--	多条记录
--		当 Z∊[-inf, 10]时，Y <= 5
--		当 Z∊(10,   20]时，Y <= 4
--		当 Z∊(20,   30]时，Y <= 3
--		当 Z∊(30, +inf]时，Y <= 2
SELECT
	*
FROM
	clean_order
WHERE
	dt = 20180502 AND
  sku = 104436 AND
  werks = 1166
ORDER BY
	raw_qty DESC
LIMIT 2;
