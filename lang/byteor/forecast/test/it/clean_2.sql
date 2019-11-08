-- Author: Rong Jian <jian.rong@dmall.com>
-- Review: Zhou Peng <peng.zhou@dmall.com>

-- 被clean_2清洗
SELECT
	sku,
	werks,
	promo_label
FROM
	clean_order
WHERE
	dt = 20180501 AND
  clean_flag = 'clean_2'
LIMIT 10;

-- 该店该品当日小票数量
-- 预期 < 5 且 > 1
SELECT
	count(*)
FROM
	clean_order
WHERE
	dt = 20180426 AND
  sku = 178332 AND
  werks = 1169;

-- 商品中分类
SELECT
	middle_class
FROM
	etl_class
WHERE
	sku = 178332;

-- 门店所属分组
-- clean_order.promo_label = 0,则type = normal
-- clean_order.promo_label = 1,则type = prom
SELECT
	label
FROM
	preprocess_labelwerks
WHERE
	vender_id = 1 AND
  middle_class = 161 AND
  werks = 1169 AND
  type = 'normal';

-- 该门店所属门店类中所有该sku的当日小票数量
-- 预期
-- >= 5 (clean_2_1)
-- < 5 (clean_2_2)
SELECT
	count(*)
FROM
	clean_order t
LEFT semi JOIN
  preprocess_labelwerks a
ON t.werks = a.werks AND
   a.vender_id = 1 AND
   a.middle_class = 161 AND
   a.label = 1 AND
   t.dt = 20180426 AND
   t.sku = 178332;

-- 该店该品最近半年销量中位数设为Z
-- clean_order.promo_label=0,则type=normal,
-- clean_order.promo_label=1,则type=prom
SELECT
	qty_median
FROM
	preprocess_sixmonth
WHERE
	dt = 20180426 AND
  sku = 178332 AND
  werks = 1169 AND
  type = 'normal';

-- 该店该品当日小票数量top2
-- 预期
--	当Z∊[-inf, 10]时，Y > 5
--	当Z∊(10,   20]时，Y > 4
--	当Z∊(20,   30]时，Y > 3
--	当Z∊(30, +inf]时，Y > 2
SELECT
	*
FROM
	clean_order
WHERE
	dt = 20180426 AND
  sku = 178332 AND
  werks = 1169
ORDER BY
	raw_qty DESC
LIMIT 2;


-- clean_2_2
-- 该门店所属门店类中所有该sku的近一周小票数量
-- 预期
-- >= 5 (clean_2_2)
-- < 5 (clean_2_3)
SELECT
	count(*)
FROM
	clean_order t
LEFT semi JOIN
  preprocess_labelwerks a
ON t.werks = a.werks AND
   a.vender_id = 1 AND
   a.middle_class = 161 AND
   t.dt <= 20180426 AND
   t.dt > 20180426 - 7 AND
   t.sku = 178332;
