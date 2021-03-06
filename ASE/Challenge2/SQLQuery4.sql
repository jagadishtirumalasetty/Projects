USE [iVolunteer]
GO
/****** Object:  Table [dbo].[UserProfile]    Script Date: 10/27/2014 14:27:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[UserProfile](
	[UserId] [varchar](20) NOT NULL,
	[FirstName] [varchar](50) NOT NULL,
	[LastName] [varchar](50) NOT NULL,
	[DisplayName] [varchar](10) NULL,
	[IsGoogle] [bit] NULL,
	[Sex] [char](1) NOT NULL,
	[DOB] [varchar](10) NOT NULL,
	[Address1] [varchar](50) NULL,
	[Address2] [varchar](50) NULL,
	[City] [varchar](50) NULL,
	[State] [varchar](50) NULL,
	[ZipCode] [int] NULL,
	[Emailid] [varchar](50) NULL,
	[phone] [varchar](15) NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[UserLog]    Script Date: 10/27/2014 14:27:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[UserLog](
	[UserId] [varchar](20) NOT NULL,
	[IsGoogle] [bit] NULL,
	[RequestId] [int] NULL,
	[isVolunteer] [int] NULL,
	[Credibility] [int] NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Request]    Script Date: 10/27/2014 14:27:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Request](
	[RequestID] [bigint] NOT NULL,
	[Description] [varchar](500) NOT NULL,
	[DateTime] [varchar](20) NOT NULL,
	[Location] [varchar](100) NOT NULL,
	[RequesterId] [varchar](20) NOT NULL,
	[VolunteerId] [varchar](20) NULL,
	[Status] [varchar](10) NOT NULL,
	[RespondedDateTime] [varchar](20) NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Login]    Script Date: 10/27/2014 14:27:20 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Login](
	[UserId] [varchar](20) NOT NULL,
	[Password] [varchar](20) NOT NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  StoredProcedure [dbo].[CreateRequest]    Script Date: 10/27/2014 14:27:18 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
/*Procedure to authenticate a User
Jagadish_T
Oct 26, 2014
*/


create proc [dbo].[CreateRequest](
@Userid varchar(20),
@desc varchar(500),
@loc varchar(200)
)
as
begin

declare @id bigint = cast((cast(DATEPART(yyyy,getdate()) as varchar(4))
						+ cast(DATEPART(mm,getdate()) as varchar(4))
						+ cast(DATEPART(dd,getdate()) as varchar(4))
						+ cast(DATEPART(hh,getdate()) as varchar(4))
						+ cast(DATEPART(mm,getdate()) as varchar(4))
						+ cast(DATEPART(ss,getdate()) as varchar(4))) as bigint);

INSERT INTO [iVolunteer].[dbo].[Request]
           ([RequestID]
           ,[Description]
           ,[DateTime]
           ,[Location]
           ,[RequesterId]
           ,[VolunteerId]
           ,[Status]
           ,[RespondedDateTime])
     VALUES
           (@id
           ,@desc
           ,GETDATE()
           ,@loc
           ,@id
           ,null
           ,0
           ,null)
 
end

--exec AuthenticateUser 'Jagadish','123'
--select COUNT(0) from dbo.[Login] where UserId = 'Jagadish'
GO
/****** Object:  StoredProcedure [dbo].[AuthenticateUser]    Script Date: 10/27/2014 14:27:18 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
/*Procedure to authenticate a User
Jagadish_T
Oct 9, 2014
*/


CREATE proc [dbo].[AuthenticateUser](
@Userid varchar(20),
@password varchar(20)
)
as
begin

	if exists (select [UserId] from dbo.[Login] where UserId = @Userid)
	begin
		if exists (select [Password] from dbo.[Login] where UserId = @Userid and [Password] = @password)
		begin
			select 'OK'
		end
		else
		begin	
			select 'Invalid Password'
		end
		
	end
	else
	begin
		select 'Invalid Username'
	end
end

--exec AuthenticateUser 'Jagadish','123'
--select COUNT(0) from dbo.[Login] where UserId = 'Jagadish'
GO
