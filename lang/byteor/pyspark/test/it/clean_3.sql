-- Author: Rong Jian <jian.rong@dmall.com>
-- Review: Zhou Peng <peng.zhou@dmall.com>

-- 被clean_3清洗
SELECT
	sku,
	werks,
	promo_label,
	raw_qty
FROM
	clean_order
WHERE
	dt = 20180502 AND
  clean_flag = 'clean_3'
LIMIT 10;

-- 该店该品最近半年销量中位数 设为Y
-- clean_order.promo_label=0, 则type=normal,
-- clean_order.promo_label=1, 则type=prom
SELECT
	qty_median
FROM
	preprocess_sixmonth
WHERE
	dt = 20180502 AND
  sku = 513096 AND
  werks = 1530 AND
  type = 'normal';

-- 小票销量
-- 预期 >= 阈值 * Y
SELECT
	raw_qty
FROM
	clean_order
WHERE
	dt = 20180502 AND
  sku = 513096 AND
  werks = 1530 AND
  clean_flag = 'clean_3';
