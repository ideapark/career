-- Author: Rong Jian <jian.rong@dmall.com>
-- Review: Zhou Peng <peng.zhou@dmall.com>

-- 被clean_1清洗
SELECT
	sku,
	werks,
	promo_label
FROM
	clean_order
WHERE
	dt = 20180501 AND
  clean_flag = 'clean_1'
LIMIT 10;

-- 该店该品当日小票数量
-- 预期 >= 5
SELECT
	count(*)
FROM
	clean_order
WHERE
	dt = 20180501 AND
  sku = 654584 AND
  werks = 1028;

-- 该店该品最近半年销量中位数设为Z
-- clean_order.promo_label = 0, 则type = normal
-- clean_order.promo_label = 1, 则type = prom
SELECT
	qty_median
FROM
	preprocess_sixmonth
WHERE
	dt = 20180501 AND
  sku = 654584 AND
  werks = 1028 AND
  type = 'normal';

-- 该店该品当日小票销量top2
-- 第一行salequantityde/第二行salequantityde即为该店该品当日小票最大值No.1/该店该品当日小票第二大值No.2设为Y
-- 预期
--  当Z∊[-inf, 10]时，Y > 5
--  当Z∊(10,   20]时，Y > 4
--  当Z∊(20,   30]时，Y > 3
--  当Z∊(30, +inf]时，Y > 2
SELECT
	*
FROM
	clean_order
WHERE
	dt = 20180501 AND
  sku = 654584 AND
  werks = 1028
ORDER BY
	raw_qty DESC
LIMIT 2;


-- 找中位数在指定范围的sku,werks
SELECT
	t.*
FROM
	preprocess_sixmonth t,
	clean_order a
WHERE
	t.dt = 20180501 AND
  t.sku = a.sku AND
  t.werks = a.werks AND
  a.dt = 20180501 AND
  a.clean_flag = 'clean_1' AND
  t.qty_median > 20
LIMIT 10;

-- 该店该品当日小票数量top2
SELECT
	*
FROM
	clean_order
WHERE
	dt = 20180501 AND
  sku = 654584 AND
  werks = 1028
ORDER BY
	raw_qty DESC
LIMIT 2;
