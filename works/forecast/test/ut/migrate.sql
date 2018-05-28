-- ETL

-- OK
select * from wumart2dmall.etl_promoplanitem_sigma limit 10;
select * from wumart2dmall.etl_promoplanitemsite_sigma limit 10;

-- OK
select count(*) from wumart2dmall.m_zpromotionplanitem;
select count(*) from wumart2dmall.etl_promoplanitem_sigma;

-- OK
select count(*) from wumart2dmall.m_zpromotionplanitemsite;
select count(*) from wumart2dmall.etl_promoplanitemsite_sigma;

-- PREPROCESS

-- NOK
select * from wumart2dmall.preprocess_labelwerks where vender_id=1 limit 10;

-- OK
select * from wumart2dmall.preprocess_sixmonth where vender_id=1 and dt=20180409 limit 10;

-- OK
select * from wumart2dmall.preprocess_oneweek where vender_id=1 and dt=20180409 limit 10;

-- CLEAN

-- OK
select * from wumart2dmall.clean_order where vender_id=1 and dt=20180409 limit 10;

-- DMS

-- OK
select * from wumart2dmall.forecast_dms_data where vender_id=1 and dt=20180409 limit 10;
