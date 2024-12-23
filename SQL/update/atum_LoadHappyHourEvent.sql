USE [atum2_db_1]
GO
/****** Object:  StoredProcedure [dbo].[atum_LoadHappyHourEvent]    Script Date: 01/04/2017 17:40:31 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER OFF
GO
-----------------------------------------------------------------------------
-- 2005-03-30 by cmkwon, HappyHourEvent Â°Ã¼Â·Ãƒ

-- Â¸Ã°ÂµÃ§ ServerGroup Ã€ÃŒÂºÂ¥Ã†Â®, Ã‡Ã¶Ã€Ã§ Â¼Â­Â¹Ã¶Â±Âº Ã€ÃŒÂºÂ¥Ã†Â® Â°Â¡ÃÂ®Â¿Ã€Â±Ã¢
-- 2006-08-25 by cmkwon, @i_ServerGroupID		INT ÃƒÃŸÂ°Â¡Ã‡Ã”
-- // 2007-10-30 by cmkwon, Â¼Â¼Â·Ã‚ÂºÂ° Ã‡Ã˜Ã‡Ã‡Â¾Ã†Â¿Ã¶ Ã€ÃŒÂºÂ¥Ã†Â® Â±Â¸Ã‡Ã¶ - Ã‡ÃŠÂµÃ¥ ÃƒÃŸÂ°Â¡(InfluenceType)
-- 2008-03-13 by dhjin, LevelÂºÂ° Ã‡Ã˜Ã‡Ã‡Â¾Ã†Â¿Ã¶ Ã€ÃŒÂºÂ¥Ã†Â® Â±Â¸Ã‡Ã¶ - MinLevel, MaxLevel Ã‡ÃŠÂµÃ¥ ÃƒÃŸÂ°Â¡
ALTER PROCEDURE [dbo].[atum_LoadHappyHourEvent]
--	@i_ServerGroupID		INT				-- 2006-08-25 by cmkwon, 0(=AllServerGroup), 1(=10061), 2(10062), ...
AS
	-- // 2007-10-30 by cmkwon, Â¼Â¼Â·Ã‚ÂºÂ° Ã‡Ã˜Ã‡Ã‡Â¾Ã†Â¿Ã¶ Ã€ÃŒÂºÂ¥Ã†Â® Â±Â¸Ã‡Ã¶ - Ã‡ÃŠÂµÃ¥ ÃƒÃŸÂ°Â¡(InfluenceType)Â¿Ã Â¾Ã†Â·Â¡Â¿Ã Â°Â°Ã€ÃŒ Ã‡ÃŠÂµÃ¥Â¸Ã­ Â¸Ã­Â½ÃƒÂ·ÃŽ Â¼Ã¶ÃÂ¤Ã‡Ã”
	--SELECT * 
	--	FROM ti_HappyHourEvent WITH (NOLOCK)
	--	WHERE ServerGroupID= 0 OR ServerGroupID= @i_ServerGroupID
	--	ORDER BY DayOfWeek, StartTime
	SELECT UniqueNumber, ServerGroupID, DayOfWeek, StartTime, EndTime, EXPRate, SPIRate, EXPRepairRate, DropItemRate, DropRareItemRate
			, WarPointRate, InfluenceType, MinLevel, MaxLevel
	FROM atum2_db_account.dbo.ti_HappyHourEvent WITH (NOLOCK)
	WHERE ServerGroupID= 0
	ORDER BY InfluenceType, DayOfWeek, StartTime



