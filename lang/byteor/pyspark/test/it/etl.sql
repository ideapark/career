-- Author: Rong Jian <jian.rong@dmall.com>
-- Review: Zhou Peng <peng.zhou@dmall.com>

-- 增量表和全量表中，促销状态应该相同
-- 预期 0
SELECT
	*
FROM
	etl_promoplanitem_sigma a,
	ods_zpromotionplanitem_day b
WHERE b.dt = 20180503 AND
      a.mandt = b.mandt AND
      a.ref_promo = b.ref_promo AND
      a.matnr = b.matnr AND
      a.aktnr = b.aktnr AND
      a.pstop != b.pstop;


-- 预期 0
SELECT
	*
FROM
	etl_promoplanitemsite_sigma a,
	ods_zpromotionplanitemsite_day b
WHERE
	b.dt = 20180503 AND
  a.mandt = b.mandt AND
  a.werks = b.werks AND
  a.ref_promo = b.ref_promo AND
  a.matnr = b.matnr AND
  a.aktnr = b.aktnr AND
  (a.vkdab != b.vkdab OR a.vkdbi != b.vkdbi);


-- 增量表中的sku应该都在全量表中存在
-- 预期 0
SELECT
	*
FROM
	ods_zpromotionplanitem_day a
LEFT JOIN
  etl_promoplanitem_sigma b
ON a.dt = 20180425 AND
   a.aktnr = b.aktnr AND
   a.matnr = b.matnr AND
   a.ref_promo = b.ref_promo AND
   a.mandt = b.mandt
WHERE
	b.matnr IS NULL AND
  a.dt = 20180425;


-- 预期 0
SELECT
	*
FROM
	ods_zpromotionplanitemsite_day a
LEFT JOIN
  etl_promoplanitemsite_sigma b
ON a.dt = 20180425 AND
   a.aktnr = b.aktnr AND
   a.matnr = b.matnr AND
   a.ref_promo = b.ref_promo AND
   a.mandt = b.mandt AND
   a.werks = b.werks
WHERE
	b.matnr IS NULL AND
  a.dt = 20180425;
