-- 正常:type="normal"
-- 促销:type="prom"

-- 门店分类结果
select count(*) from wumart2dmall.dms_mc_werks_cluster where vender_id=1 and type='normal';
select count(*) from wumart2dmall.preprocess_labelwerks where vender_id=1 and type='normal';

select * from wumart2dmall.dms_mc_werks_cluster where vender_id=1 and type='normal' and mc=129 and (werks=1313 or werks=1129);
select * from wumart2dmall.preprocess_labelwerks where vender_id=1 and type='normal' and mc=129 and (werks=1313 or werks=1129);

-- 最近6个月销量中位数
select count(*) from wumart2dmall.dms_data_clean_year where vender_id=1 and type='normal' and dt=20180315;
select count(*) from wumart2dmall.preprocess_sixmonth where vender_id=1 and type='normal' and dt=20180315;

select * from wumart2dmall.dms_data_clean_year where vender_id=1 and type='normal' and werks=1313 and dt=20180315 order by sku limit 20;
select * from wumart2dmall.preprocess_sixmonth where vender_id=1 and type='normal' and werks=1313 and dt=20180315 order by sku limit 20;

-- 最近一周销量中位数及金额
select count(*) from wumart2dmall.dms_data_clean_recent where vender_id=1 and type='prom' and dt=20180315;
select count(*) from wumart2dmall.preprocess_oneweek where vender_id=1 and type='prom' and dt=20180315;

select * from wumart2dmall.dms_data_clean_recent where vender_id=1 and type='normal' and dt=20180315 order by mandt, sku limit 30;
select * from wumart2dmall.preprocess_oneweek where vender_id=1 and type='normal' and dt=20180315 order by mandt, sku limit 30;
