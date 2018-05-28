-- Author: Rong Jian <jian.rong@dmall.com>
-- Review: Zhou Peng <peng.zhou@dmall.com>

-- 昨日是开档日
-- 预期 0
SELECT
	sale * salerate + dms_n_old * olddmsrate dms_forecast,
	dms,
	ROUND(sale * salerate + dms_n_old * olddmsrate - dms, 2) difference,
	*
FROM
	dms_data
WHERE
	yesterday_is_prom_start = 1 AND
  sale_flag = 1 AND
  salerate > 0 AND
  olddmsrate > 0 AND
  dt = 20180508 AND
  STATUS IN ('1', '2', '3', '4', '4 ', '4G', '5', '7', '7 ') AND
  (ROUND(sale * salerate + dms_n_old * olddmsrate - dms, 2) > 0	 -- 公式计算的dms与系统计算的dms差异大于0（两位小数）
	 OR dms_n != dms_n_old	                                       -- 今日正常dms ≠ 昨日正常dms
	 OR dms_p != dms);	                                           -- 今日dms ≠ 今日促销dms


-- 昨日是促销日
-- 预期 0
SELECT
	sale * salerate + dms_p_old * olddmsrate dms_forecast,
	dms,
	ROUND(sale * salerate + dms_p_old * olddmsrate - dms, 2) difference,
	*
FROM
	dms_data
WHERE
    yesterday_is_prom_start = 0 AND
    yesterday_is_prom = 1 AND
    sale_flag = 1 AND
    salerate > 0 AND
    olddmsrate > 0 AND
    dt = 20180508 AND
    STATUS IN ('1', '2', '3', '4', '4 ', '4G', '5', '7', '7 ') AND
    (ROUND(sale * salerate + dms_n_old * olddmsrate - dms, 2) > 0   -- 公式计算的dms与系统计算的dms差异大于0（两位小数）
  	 OR dms_n != dms_n_old	                                        -- 今日正常dms ≠ 昨日正常dms
	   OR dms_p != dms);	                                            -- 今日dms ≠ 今日促销dms


-- 昨日无促销
-- 预期 0
SELECT
	sale * salerate + dms_n_old * olddmsrate dms_forecast,
	dms,
	ROUND(sale * salerate + dms_n_old * olddmsrate - dms, 2) difference,
	*
FROM
	dms_data
WHERE
	yesterday_is_prom = 0 AND
  sale_flag = 1 AND
  salerate > 0 AND
  olddmsrate > 0 AND
  dt = 20180508 AND
  STATUS IN ('1', '2', '3', '4', '4 ', '4G', '5', '7', '7 ') AND
  (ROUND(sale * salerate + dms_n_old * olddmsrate - dms, 2) > 0	 -- 公式计算的dms与系统计算的dms差异大于0（两位小数）
	 OR dms_p != dms_p_old	                                       -- 今日促销dms ≠ 昨日促销dms
	 OR dms_n != dms);	                                           -- 今日dms ≠ 今日正常dms


-- 昨日库存<=0.25倍前一日的DMS，今日DMS取昨日DMS
-- 预期 0
SELECT
	*
FROM
	dms_data a
LEFT SEMI JOIN
  dms_data b
ON a.sku = b.sku AND
   a.werks = b.werks AND
   a.dt = b.dt + 1 AND
   a.dt = 20180508
WHERE
	a.sale_flag = 1 AND
  a.STATUS IN ('1', '2', '3', '4', '4 ', '4G', '5', '7', '7 ') AND
  0.25 * a.dms_old >= a.stock AND                -- 昨日库存<=0.25倍前一日的DMS
  a.today_is_prom_start != 1 AND                 -- 今天不是促销开始
  a.yesterday_is_prom = b.yesterday_is_prom AND  -- 昨天和前天促销状态一样(都是促销或者都是非促销)
  a.dms != a.dms_old;


-- 不需要计算DMS的状态的商品，今日DMS取昨日DMS
-- 预期 0
SELECT
	*
FROM
	dms_data
WHERE
	STATUS NOT IN ('1', '2', '3', '4', '4 ', '4G', '5', '7', '7 ') AND
  ((dms <> dms_n_old AND dms <> dms_p_old) OR dms_n <> dms_n_old OR dms_p <> dms_p_old) AND
  dt = 20180503
LIMIT 100;


-- 一年无销售记录的商品，dms取0
-- 预期 0
SELECT
	*
FROM
	dms_data
WHERE
	dt = 20180503 AND
  dms + dms_n + dms_p <> 0
  AND sale_flag = 0;


-- dms_data.dms_old取值验证
-- 预期 0
SELECT
	*
FROM
	dms_data a
LEFT SEMI JOIN
  dms_data b
ON a.sku = b.sku AND
   a.werks = b.werks AND
   a.dt = b.dt + 1 AND
   a.dt = 20180509
WHERE
	a.dms_old != b.dms;


-- dms_data.salerate，dms_data.olddmsrate 取值验证
SELECT
	b.sku,
	b.werks,
	b.yesterday_is_prom,
	b.yesterday_is_prom_start,
	b.date_type,
	b.salerate,
	b.olddmsrate
FROM
	etl_class a
LEFT SEMI JOIN
  dms_data b
ON a.big_class = 'UG6' AND
   a.sku = b.sku AND
   b.werks = 1033
WHERE
	dt = 20180509 AND
  b.salerate > 0
LIMIT 100;


-- dms_data.sale取值验证
-- 预期 0
SELECT
	*
FROM
	(
		SELECT
			sum(a.raw_qty) sales,
			b.sale,
			b.sku,
			b.werks,
			sum(a.raw_qty) - b.sale different
		FROM
			clean_order a,
			dms_data b
		WHERE
			a.sku = b.sku AND
      a.werks = b.werks AND
      a.promo_label = b.yesterday_is_prom AND
      a.dt = b.dt - 1 AND
      a.dt = 20180508
		GROUP BY
			b.sale,b.werks,b.sku
	) t
WHERE
	ROUND(t.different, 2) > 0


-- dms_data.stock取值验证
-- 预期 0
SELECT
	a.sku,
	a.werks,
	a.stock,
	b.labst
FROM
	dms_data a
LEFT JOIN
  ods_zscmexc b
ON a.werks = b.werks AND
   a.dt = b.dt + 2 AND
   a.dt = 20180509 AND
   b.matnr = CONCAT('000000000000', a.sku)
WHERE
	ROUND(a.stock - b.labst, 2) > 0
