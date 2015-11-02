<div id="export-history" class="modal hide fade">
	<span class="loading-lg"></span>
</div>
<div id="history-filters" class="modal hide fade">
	<span class="loading-lg"></span>
</div>
<div id="history-notes" class="modal hide fade">
	<span class="loading-lg"></span>
</div>
<div id="history-dispositions" class="modal hide fade">
	<span class="loading-lg"></span>
</div>
<div id="history-trace" class="modal hide fade">
	<span class="loading-lg"></span>
</div>

<div class="action-container-row">
	<div class="action-container-left">
		<?php
	   // echo $this->Form->hidden('');
			echo '&nbsp;';
			echo $this->Html->link(
			$this->I18n->i18n('Filters'),
			array('action' => 'filters'),
			array(
				'class' => 'btn',
				'onclick' => 'loadModal("#history-filters", $(this).attr("href"));',
				'data-target' => '#history-filters',
				'data-toggle' => 'modal',
				'data-backdrop' => 'static',
			)
		);
	  ?>
		<?php 
		/*setup the active filters panel */
		if (isset($filters['start_date']) && isset($filters['end_date'])) {
			// $startDate = date("F jS, Y g:i a",strtotime($filters['start_date']));
			// $endDate = date("F jS, Y g:i a",strtotime($filters['end_date']));

			
			if ($this->Uiconfig->isUiConfig("PORTAL_CALL_HISTORY_SHOW_FILTER_TIME","no")) {
				$startDate = date( 'm/d/Y H:i', strtotime($filters['start_date']));
				$endDate = date( 'm/d/Y H:i', strtotime($filters['end_date']));
			}
			else {
				$startDate = date( 'm/d/Y ', strtotime($filters['start_date']));
				$endDate = date( 'm/d/Y ', strtotime($filters['end_date']));
			}
			

			echo "<a id='filter-date' onclick='loadModal(\"#history-filters\", $(this).attr(\"href\"));' href='/portal/callhistory/filters' data-target='#history-filters' data-toggle='modal' data-backdrop='static' class='badge badge-info set-filters'>".$startDate." &mdash; ".$endDate."</a>";

		}
		
		if (isset($filters['type'])  )
			
			echo "<span id=\"filter-type\" class=\"badge badge-info  set-filters clear-filter\">" .$filters['type'] . " Calls" .
			$this->Html->link(
				'&times;',
				array('action' => 'remove_filter','type'),
				array('class' => 'clear-filter', 'escape' => false)
			) . 
			" </span>";
		if (isset($filters['user']) )
		{
			if($this->Session->check('queueAndAgentList') &&  $this->Session->read('layout_type') == "navigation_omp" && $this->Session->read('sub_scope') == "Call Center Supervisor")
			{
				$details = $this->Session->read('queueAndAgentList');
				if ($this->Session->read('sub_user') == $filters['user'])
					echo "<span id=\"filter-user\" class=\"badge badge-info  set-filters clear-filter\"> My Calls &nbsp; </span> ";
				else
					echo "<span id=\"filter-user\" class=\"badge badge-info  set-filters clear-filter\">". $details[$filters['user']] ."&nbsp; </span> ";
			}
			else if ($this->Session->read('layout_type')!='navigation_user') 
				echo "<span id=\"filter-user\" class=\"badge badge-info  set-filters clear-filter\">".$this->I18n->i18n("User").": ".$filters['user'] .
				$this->Html->link(
					'&times;',
					array('action' => 'remove_filter','user'),
					array('class' => 'clear-filter', 'escape' => false)
				) . 
				" </span>";
		}
		if (isset($filters['domain']) )
		{
			if ($this->Session->read('layout_type')=='navigation_reseller')
				echo "<span id=\"filter-user\" class=\"badge badge-info  set-filters clear-filter\">".$this->I18n->i18n("Domain").": ".$filters['domain'] .
				$this->Html->link(
						'&times;',
						array('action' => 'remove_filter','domain'),
						array('class' => 'clear-filter', 'escape' => false)
				) .
				" </span>";
		}
		if (isset($filters['caller']) )
			echo "<span id=\"filter-user\" class=\"badge badge-info  set-filters clear-filter\">".$this->I18n->i18n("Caller").": ".$filters['caller'] .
				$this->Html->link(
						'&times;',
						array('action' => 'remove_filter','caller'),
						array('class' => 'clear-filter', 'escape' => false)
				) .
				" </span>";
		if (isset($filters['dialled']) )
			echo "<span id=\"filter-dialed\" class=\"badge badge-info  set-filters clear-filter\">".$this->I18n->i18n("Dialed").": ".$filters['dialled'] .
			$this->Html->link(
				'&times;',
				array('action' => 'remove_filter','dialled'),
				array('class' => 'clear-filter', 'escape' => false)
			) . 
			" </span>";
		 ?>
		
		
	</div>
	<div class="action-container-right">
	<?php

	// 	echo $this->Html->link(
	// 		'Disposition Settings',
	// 		array('action' => 'dispositions'),
	// 		array(
	// 			'class' => 'btn',
	//			'onclick' => 'loadModal("#history-dispositions", $(this).attr("href"))',
	// 			'data-target' => '#history-dispositions',
	// 			'data-toggle' => 'modal',
	// 			'data-backdrop' => 'static',
	// 		)
	// 	);
	?>
	<?php
		if ($this->Uiconfig->isUiConfig("PORTAL_CALLHISTORY_EXPORT","yes"))
		{
			echo '&nbsp;';
			// echo $this->Html->link(
			// 	$this->I18n->i18n("Export"),
			// 	array('action' => 'export.csv'),
			// 	array(
			// 		'class' => 'btn helpsy',
			// 		'title' => $this->I18n->i18n("Download Call Data"),
			// 		'data-loading-text' => 'Exporting...'
			// 		)
			// );
			?>
			<button class="btn download-file helpsy" title="<?php echo $this->I18n->i18n("Download Call Data");?>" data-download-path="/portal/callhistory/export.csv" data-download-disable="true"><?php echo __('Export');?></button>
			<?php
		}
		if ($this->Uiconfig->isUiConfig("PORTAL_CALLHISTORY_EXPORT_BILLABLE","no") && isset($filters['domain']))
		{
			$expires= gmdate("Y-m-d H:i:s", time() + 3600);
			$salt= "3rdPartBillable";
			
			$prehash = $salt.$filters['domain'].$filters['start_date'].$filters['end_date'].$expires;
			$params = "domain=".$filters['domain']."&start_date=".urlencode($filters['start_date'])."&end_date=".
			urlencode($filters['end_date'])."&expires=".urlencode($expires)."&hash=".md5($prehash);
			
			if(isset($thirdParty))
				$params.=$thirdParty;
					
			echo '&nbsp;';
			echo $this->Html->link(
					$this->Uiconfig->getUiConfig("PORTAL_CALLHISTORY_EXPORT_BILLABLE_TEXT", "Billable Calls"),
					$this->Uiconfig->getUiConfig("PORTAL_CALLHISTORY_EXPORT_BILLABLE_URL","billable.php")."?".$params,
					array('class' => 'btn helpsy','onclick'=>'$(this).attr("disabled",true);','title' => $this->Uiconfig->getUiConfig("PORTAL_CALLHISTORY_EXPORT_BILLABLE_TITLE",""))
			);
		}
	?>


	</div>
</div>
<?php
if ($this->Session->read('layout_type') == "navigation_user") {?>
  <div class="callhistory-panel-main callhistory-user">
<?php } else { ?>
  <div class="callhistory-panel-main">
<?php }
	$jsRecLookup= array();
	
	
	
	
	if (empty($cdrs)) {
		echo '<div class="nonecreated"><h3>'.$this->I18n->i18n("No calls have been found.").'</h3></div>';
	}
	else {
		$uid= $this->Session->read('sub_user')."@".$this->Session->read('sub_domain');
		
		if ($this->Session->read('layout_type')=="navigation_user" )
		{
		}
		else if ($this->Uiconfig->isUiConfig("PORTAL_CALL_HISTORY_CLICK_TO_DIAL_MANAGER","yes") && $this->Session->read('layout_type') == "navigation_omp")
		{
		}
		else
			$uid =null;

		/* Retrieve and set various settings for call history. */
		$addNotes = false;
		$addRec = false;
		$addDispIndex=false;
		$addReasonIndex=false;
		$addPAC=false;
		$addAlias=false;
		$addQOS=false;

		$addRoute=false;
		$addReleaseReason=false;

		if ($this->Uiconfig->isUiConfig("PORTAL_CALL_HISTORY_SHOW_RECORDINGS",$this->Session->read('layout_type') == "navigation_omp"?"yes":"no"))
			$addRec =true;
		if ($this->Uiconfig->isUiConfig("PORTAL_CALL_HISTORY_SHOW_DISP_NOTES",$this->Session->check('callcenter_user')?"yes":"no"))
			$addNotes=true;
		if ($this->Uiconfig->isUiConfig("PORTAL_CALL_HISTORY_SHOW_DISP_ON_INDEX","no"))
			$addDispIndex=true;
		if ($this->Uiconfig->isUiConfig("PORTAL_CALL_HISTORY_SHOW_REASON_ON_INDEX","no"))
			$addReasonIndex=true;
		if ($this->Uiconfig->isUiConfig("PORTAL_CALL_HISTORY_SHOW_PAC","no"))
			$addPAC=true;
		if ($this->Uiconfig->isUiConfig("PORTAL_PHONENUMBER_SHOW_ALIAS","no"))
			$addAlias=true;

		if ($this->Session->read('layout_type') == "navigation_omp" || $this->Session->read('layout_type') == "navigation_reseller")
		{
    		if ($this->Uiconfig->isUiConfig("PORTAL_CALL_HISTORY_SHOW_ROUTE","no"))
    			$addRoute=true;
    		if ($this->Uiconfig->isUiConfig("PORTAL_CALL_HISTORY_SHOW_RELEASE_REASON","no"))
    			$addReleaseReason=true;
		}
		
		if ($this->Uiconfig->isUiConfig("PORTAL_CALL_HISTORY_SHOW_QOS","no"))
		{
			$addQOS=true;
			if (!class_exists('$this->Qos')) {
				App::import('Helper', 'Qos');
				$this->Qos = new QosHelper();
			}	
		}

		/* if there is an extra setting, it will crowd the table too much. make table font smaller to compensate in this case */
		if ($this->Session->read('layout_type') ==  "navigation_reseller" && ($addDispIndex || $addReasonIndex || $addPAC || $addAlias || $addQOS))
			$tableSmaller = 'table-smaller';
		else
			$tableSmaller = '';

		/* Generate table for call history. */
		echo $this->Html->tag('div', null, array('class' => 'table-container'));
		echo $this->Html->tag('table', null, array('class' => 'table table-condensed table-hover fixed-table-header ' . $tableSmaller));
		echo $this->Html->tag('thead');
		echo $this->Html->tag('tr');
		
			
		if ($this->Session->read('sub_scope') == "Super User" || $this->Session->read('sub_scope') == "Reseller")
		{
			if ($this->Uiconfig->isUiConfig("PORTAL_CALL_HISTORY_SHOW_TRACE",$this->Session->read('sub_scope') == "Super User"?"yes":"no"))
				$addTrace =true;
		}
		elseif ($this->Uiconfig->isUiConfig("PORTAL_CALL_HISTORY_SHOW_TRACE_OMP","no"))
        {
            $addTrace =true;
        }
		    
		$arry_headers = array();
		if ($this->Session->read('layout_type') == "navigation_user") {
			$arry_headers = array(
				'<th>&nbsp;</th>',
				'<th>'.$this->I18n->i18n('Number').'</th>',
				'<th>'.$this->I18n->i18n('Name').'</th>',
				'<th class="text-right">'.$this->Paginator->sort($this->I18n->i18n('Date'), 'call_end').'</th>',
				'<th class="text-right">'.$this->I18n->i18n('Duration').'</th>'
			);
		}
		elseif ($this->Session->read('layout_type') ==  "navigation_omp" || $this->Session->read('layout_type') == "navigation_reseller")
		{
			
			if ($this->Session->read('layout_type') == "navigation_reseller")
				$arry_headers = array('<th>'.$this->I18n->i18n('Domain').'</th>', '<th>'.$this->I18n->i18n('From Name').'</th>','<th>'.$this->I18n->i18n('From').'</th>');
			else
				$arry_headers = array('<th>'.$this->I18n->i18n('From Name').'</th>','<th>'.$this->I18n->i18n('From').'</th>');

			if ($addQOS) 
				$arry_headers[] = '<th>'.$this->I18n->i18n('QOS').'</th>';

			$arry_headers[] = '<th>'.$this->I18n->i18n('Dialed').'</th>';

			if ($addAlias)
				$arry_headers[] = '<th>'.$this->I18n->i18n('To Name').'</th>';

			$arry_headers[] = '<th>'.$this->I18n->i18n('To').'</th>';

			if ($addQOS) 
				$arry_headers[] = '<th>'.$this->I18n->i18n('QOS').'</th>';
			
			$arry_headers[] = '<th class="text-right">'.$this->Paginator->sort($this->I18n->i18n('Date'), 'call_end').'</th>';
			$arry_headers[] = '<th class="text-right">'.$this->I18n->i18n('Duration').'</th>';

		}
				
		if ($addDispIndex)
			$arry_headers[] = '<th>'.$this->I18n->i18n('Disposition').'</th>';
		if ($addReasonIndex)
			$arry_headers[] = '<th>'.$this->I18n->i18n('Reason').'</th>';
		
		if ($addRoute)
			$arry_headers[] = '<th>'.$this->I18n->i18n('Route').'</th>';
		if ($addReleaseReason)
			$arry_headers[] = '<th>'.$this->I18n->i18n('Release Reason').'</th>';
		
		
		if ($addPAC)
			$arry_headers[] = '<th title="'.$this->I18n->i18n('Account Code').'" class="helpsy">'.$this->I18n->i18n('PAC').'</th>';
		
		$arry_headers[] = '<th>&nbsp;</th>';
		
		foreach ($arry_headers as $header) {
			echo $header;
		}

		echo $this->Html->tag('/tr');
		echo $this->Html->tag('/thead');


		$recIndex=1;

	
		foreach ($cdrs as $cdr) {
			
			if ($recIndex >= $this->Uiconfig->getUiConfig("PORTAL_CALLHISTORY_DYNAMIC_DOMAIN_MAX","5"))
				$recIndex=1;
			else 
				$recIndex++;
			$recDomain="";
			if ($this->Uiconfig->getUiConfig("PORTAL_CALLHISTORY_DYNAMIC_DOMAIN","") !="")
				$recDomain = $recIndex.$this->Uiconfig->getUiConfig("PORTAL_CALLHISTORY_DYNAMIC_DOMAIN","");
			$preload = $this->Uiconfig->getUiConfig("PORTAL_CALLHISTORY_RECORDING_PRELOAD","metadata");
				
			
 			$duration = $cdr['Callhistory']['duration'];
			if (isset($cdr['Callhistory']['domain']))
				$domain = $cdr['Callhistory']['domain'];
			else 
				$domain = $this->Session->read('sub_domain');
			
			if ($addAlias)
				$alias = $cdr['Callhistory']['did_alias'];
			
			$clean_duration = $this->Nsnumber->durationToString($duration);
			
			$clean_start_time = $this->Nstime->niceShort($cdr['Callhistory']['call_begin'] . ' GMT');
			$clean_orig_name = $cdr['Callhistory']['orig_from_name'];
			$clean_term_name ="";
			
			$clean_orig_device = $this->Phonenumber->DisplayPhoneNumber($cdr['Callhistory']['from_device'],$uid);
			
			if ($this->Uiconfig->isUiConfig('PORTAL_CALL_HISTORY_SHOW_DEVICE_USER','yes'))
			if ($this->Session->read('layout_type') == "navigation_user")
			{
				if ($cdr['Callhistory']['type'] =="inbound" ||$cdr['Callhistory']['type'] =="missed" || 
						$cdr['Callhistory']['type'] =="blocked" || $cdr['Callhistory']['type'] =="conference-inbound"  )
					if (isset($cdr['Callhistory']['orig_sub']) && isset($cdr['Callhistory']['orig_domain']) &&
					 $this->Session->read('sub_domain') ==$cdr['Callhistory']['orig_domain'] && 
					 $this->Session->read('sub_user') !=$cdr['Callhistory']['orig_sub'] )
					{
						$clean_orig_device = $this->Phonenumber->DisplayPhoneNumber($cdr['Callhistory']['orig_sub'],$uid);
					}
			}


			//if ($cdr['Callhistory']['from_device'] == "5226s")	
			//	print_r($cdr['Callhistory']);
			
			$clean_dialled = $this->Phonenumber->DisplayPhoneNumber($cdr['Callhistory']['orig_to_user'],$uid);
			
			
			
			$inter = substr($clean_dialled,0,3)=='011'?true:false;
			if ($clean_dialled =="Audio Monitoring")
				$clean_term_device="";
			else {
                     $tmp_term_device = ($this->Uiconfig->isUiConfig('PORTAL_CALL_HISTORY_SHOW_DEVICE_USER','no') &&
                            'sip' == substr($cdr['Callhistory']['to_device'], 0, 3) &&
                           (isset($cdr['Callhistory']['term_sub']) && $cdr['Callhistory']['term_sub']!="" && $cdr['Callhistory']['term_sub']!="domain"))
                           ? $cdr['Callhistory']['term_sub'] : $cdr['Callhistory']['to_device'];
                       $clean_term_device = $this->Phonenumber->DisplayPhoneNumber($tmp_term_device,$uid,true,$inter);
              }

			if ($this->Uiconfig->isUiConfig('PORTAL_CALL_HISTORY_SHOW_DEVICE_USER','yes'))
			if ($this->Session->read('layout_type') == "navigation_user")
			{
				if ($cdr['Callhistory']['type'] =="inbound" ||$cdr['Callhistory']['type'] =="missed" || 
						$cdr['Callhistory']['type'] =="blocked" || $cdr['Callhistory']['type'] =="conference-inbound"  )
				{}
				else{
					if (isset($cdr['Callhistory']['term_sub']) && isset($cdr['Callhistory']['term_domain']) 
					&& $this->Session->read('sub_domain') ==$cdr['Callhistory']['term_domain']  && 
					 $this->Session->read('sub_user') !=$cdr['Callhistory']['orig_sub']  )
					{
						 $clean_term_device = $this->Phonenumber->DisplayPhoneNumber($tmp_term_device,$uid,true,$inter);
					}
				}
			}

			$raw_dialled = $cdr['Callhistory']['orig_to_user'];
			$raw_orig_device = $cdr['Callhistory']['from_device'];
			
			$disp= $cdr['Callhistory']['disposition'];
			$reason= $cdr['Callhistory']['reason'];

		
			
			
			
			//<a href="" class="view view-timeframe" style="text-decoration:none;" rel="popover" data-content="Serves as a default when no higher-priority time frame applies." data-html="true" data-original-title="&lt;a href=&quot;/portal/timeframes/edit/netsapiens.com@*@Mobile&quot; class=&quot;helpsy-right&quot; title=&quot;Edit&quot; onclick=&quot;$(&amp;#039;#write-timeframe&amp;#039;).load(escape($(this).attr(&amp;#039;href&amp;#039;))); return false;&quot; data-target=&quot;#write-timeframe&quot; data-toggle=&quot;modal&quot; data-backdrop=&quot;static&quot;&gt;Mobile&lt;/a&gt;">Always</a>
			
			$raw_term_device = $cdr['Callhistory']['to_device'];
			
			
			if ($this->Uiconfig->isUiConfig("PORTAL_CALL_HISTORY_SHOW_RECORDINGS",$this->Session->read('layout_type') == "navigation_omp"?"yes":"no"))
			{
			/*
			if (isset($cdr['Callhistory']['recording']))
			{
				$rec = $cdr['Callhistory']['recording'];
				if (is_array($rec))
				{
					//print_r($rec);
					$audio = '<audio id="audio-'.$cdr['Callhistory']['orig_id'].'"
					data-orig-id="'.$cdr['Callhistory']['orig_id'].'"  data-term-id="'.$cdr['Callhistory']['term_id'].'" 
					controls class="cdraudio showearly" preload="none" >
					<source src="'.$rec[0]['Recording']['url'].'&convert=wav16" type="audio/wav">
					<source src="'.$rec[0]['Recording']['url'].'&convert=aac" type="audio/mp4">
					
					</audio>';
				}
				else
				{
					$audio = '<audio id="audio-'.$cdr['Callhistory']['orig_id'].'"
					data-orig-id="'.$cdr['Callhistory']['orig_id'].'"  data-term-id="'.$cdr['Callhistory']['term_id'].'" 
					controls class="cdraudio hide" preload="none" >
						
					</audio>';
				}
				
			}
			else
			{
			*/
				
 				$jsRecLookup[] = '/portal/callhistory/recording/'.$cdr['Callhistory']['orig_id']."/".$cdr['Callhistory']['term_id'];
				$audio = '<audio id="audio-'.$cdr['Callhistory']['orig_id'].'" 
				data-orig-id="'.$cdr['Callhistory']['orig_id'].'"  data-term-id="'.$cdr['Callhistory']['term_id'].'" 
				controls class="cdraudio hide" preload="'.$preload.'" >
					</audio>';
			//}

			}
			
			$download = '<a  class="download-audio disabled helpsy" title="'.$this->I18n->i18n('No Recording').'"></a>';
			$audio = '<a  class="listen disabled helpsy" title="'.$this->I18n->i18n('No Recording').'"></a>';
			
			
			$notes = $this->Html->link(
			
					"",
					array('action' => 'notes',$cdr['Callhistory']['orig_id'],$cdr['Callhistory']['term_id']),
					array(
							'class' => 'helpsy reports',
							'title' => ($cdr['Callhistory']['notes']!="" || $cdr['Callhistory']['disposition']!="")?$this->I18n->i18n("Edit Notes"):$this->I18n->i18n("Add Notes"),
							'onclick' => 'loadModal("#history-notes", $(this).attr("href"))',
							'data-target' => '#history-notes',
							'data-toggle' => 'modal',
							'data-backdrop' => 'static',
					)
			);
			
			$trace = $this->Html->link(
						
					"",
					array('action' => 'trace',str_replace(":5060","",$cdr['Callhistory']['orig_id']),str_replace(":5060","",$cdr['Callhistory']['term_id']),str_replace(":","c",$cdr['Callhistory']['call_begin']),str_replace(":","c",$cdr['Callhistory']['call_end'])),//$cdr['Callhistory']['call_begin'],$cdr['Callhistory']['call_end'],
					array(
							'class' => 'helpsy details',
							'title' => $this->I18n->i18n("Trace"),
							'onclick' => 'getTrace($(this).attr("href"));return false;',
							'data-target' => '#history-trace',
							'data-toggle' => 'modal',
							'data-backdrop' => 'static',
					)
			);
			
			
			
			
			if ($cdr['Callhistory']['to_device'] == "VMail-Account")
				$clean_term_name =$this->I18n->i18n("Voicemail");
			
			if ($clean_orig_device == "Call-Play-Account")
			    $clean_orig_device =$this->I18n->i18n("Message Playback");
			
			$btns = "";
			
			if ($addRec)
				$btns .=$download . $audio;
			if (isset($addTrace) && $addTrace)
				$btns .=$trace;
			if ($addNotes)
				$btns .=$notes;
				
			$btns = array($btns, array('class' => 'action-buttons'));
			
			
			if ($this->Session->read('layout_type') == "navigation_user")
			{
				
				$inbound_title = $cdr['Callhistory']['type'] =="missed"?$this->I18n->i18n("Missed Call"):$this->I18n->i18n("Inbound Call");
				$outbound_title = $this->I18n->i18n("Outbound Call");
				$conference_title = $this->I18n->i18n("Conference");
				$blocked_title = $this->I18n->i18n("Blocked Call");
				
				if ($cdr['Callhistory']['type'] =="inbound" ||$cdr['Callhistory']['type'] =="missed" )
					$fieldArray = array(
							"<span title='".$inbound_title."' class='helpsy " . $cdr['Callhistory']['type'] . "'></span>" ,
							$clean_orig_device,
							$this->Contacts->getContactName($raw_orig_device)?$this->Contacts->getContactName($raw_orig_device):$clean_orig_name
							);
				else if ($cdr['Callhistory']['type'] =="blocked" )
					$fieldArray = array(
							"<span title='".$blocked_title."' class='helpsy blocked'></span>" ,
							$clean_orig_device,
							$this->Contacts->getContactName($raw_orig_device)?$this->Contacts->getContactName($raw_orig_device):$clean_orig_name
							);
				else if ($cdr['Callhistory']['type'] =="conference-inbound") 
					$fieldArray = array(
							"<span title='".$conference_title."' class='helpsy " . $cdr['Callhistory']['type'] . "'></span>" ,
							$clean_orig_device,
							$this->Contacts->getContactName($raw_orig_device)?$this->Contacts->getContactName($raw_orig_device):$clean_orig_name
							);
				else if ($cdr['Callhistory']['type'] =="conference-outbound") {
					$fieldArray = array(
							"<span title='".$conference_title."' class='helpsy " . $cdr['Callhistory']['type'] . "'></span>" ,
							$clean_dialled);
					$fieldArray[] = $clean_term_name!=""?$clean_term_name:$this->Contacts->getContactName($raw_dialled);
				}
				else
				{
					$fieldArray = array(
							"<span title='".$outbound_title."' class='helpsy outbound'></span>",
							$clean_dialled);
					$fieldArray[] = $clean_term_name!=""?$clean_term_name:$this->Contacts->getContactName($raw_dialled);
				}
				
				$fieldArray[] = array($clean_start_time, array('class' => 'text-right'));
				$fieldArray[] = array($clean_duration, array('class' => 'text-right'));
				if ($addDispIndex)
					$fieldArray[] = $cdr['Callhistory']['disposition'];
				if ($addReasonIndex)
					$fieldArray[] = $cdr['Callhistory']['reason'];
				
			
				//print_r($cdr['Callhistory']['release_text']);

				if ($addPAC)
					$fieldArray[] = $cdr['Callhistory']['pac'];
				
				$fieldArray[] = $btns;	
				
				
				
				echo $this->Html->tableCells(
						array(
								$fieldArray
						),
						array('recDomain'=>$recDomain, 'recIndex'=>$recIndex,'data-orig-id' => $cdr['Callhistory']['orig_id'], 'data-term-id' => $cdr['Callhistory']['term_id']),
						array('recDomain'=>$recDomain, 'recIndex'=>$recIndex,'data-orig-id' => $cdr['Callhistory']['orig_id'], 'data-term-id' => $cdr['Callhistory']['term_id'])
				);
				
				
			}	
			elseif ($this->Session->read('layout_type') == "navigation_omp" || "navigation_reseller")
			{
				
				if ($this->Session->read('layout_type') == "navigation_reseller")
					$fieldArray = array(
							$domain,
							$clean_orig_name,
							$clean_orig_device	
					);
				else
					$fieldArray = array(
							$clean_orig_name,
							$clean_orig_device	
					);

				if ($addQOS)
					$fieldArray[] = $this->Qos->label($cdr['Callhistory'], 'orig');


				$fieldArray[] =$clean_dialled;

				if ($addAlias) {
					if(isset($alias))
						$fieldArray[] =$alias;
					else
						$fieldArray[] ='&nbsp';
				}
				
				if ($clean_term_device =="VMail" && isset($cdr['Callhistory']['term_sub']))
				{
				    $fieldArray[] =$clean_term_device. " (".$cdr['Callhistory']['term_sub'].")";
				}
				else    
				    $fieldArray[] =$clean_term_device;

				if ($addQOS)
					$fieldArray[] = $this->Qos->label($cdr['Callhistory'], 'term');

				$fieldArray[] = array($clean_start_time, array('class' => 'text-right'));
				$fieldArray[] = array($clean_duration, array('class' => 'text-right'));
				
				if ($addDispIndex)
					$fieldArray[] = $cdr['Callhistory']['disposition'];
				if ($addReasonIndex)
					$fieldArray[] = $cdr['Callhistory']['reason'];
				if ($addRoute)
					$fieldArray[] = $cdr['Callhistory']['route_to'];
				if($addReleaseReason)
					$fieldArray[] = $cdr['Callhistory']['release_text'];
				if ($addPAC)
					$fieldArray[] = $cdr['Callhistory']['pac'];

				
				
				$fieldArray[] = $btns;
				
				echo $this->Html->tableCells(
						array(
								$fieldArray
						),
						array('recDomain'=>$recDomain, 'recIndex'=>$recIndex,'data-orig-id' => $cdr['Callhistory']['orig_id'], 'data-term-id' => $cdr['Callhistory']['term_id']),
						array('recDomain'=>$recDomain, 'recIndex'=>$recIndex,'data-orig-id' => $cdr['Callhistory']['orig_id'], 'data-term-id' => $cdr['Callhistory']['term_id'])
				);
					
			}
			
		}
		echo $this->Html->tag('/table');
		echo $this->Html->tag('/div');
		
	}
?>
<?php
	if (!isset($modules)) {
		$modulus = 7;
	}
	if (!isset($model)) {
		$models = ClassRegistry::keys();
		$model = Inflector::camelize(current($models));
	}
	//print_r($this->params['paging'][$model]);
	if (($this->params['paging'][$model]['count'] > 15 || $this->params['paging'][$model]['current'] =15) && !empty($cdrs)) { ?>
	<div class="pagination-container">
		<div class="pagination pull-left">
			<ul>
				<?php echo $this->Paginator->first('<<', array('tag' => 'li')); ?>
				<?php echo $this->Paginator->prev('<', array(
					'tag' => 'li',
					'class' => 'prev',
				), $this->Paginator->link('<', array()), array(
					'tag' => 'li',
					'escape' => false,
					'class' => 'prev disabled',
				)); ?>
				
				<?php
				$page = $this->params['paging'][$model]['page'];
				$pageCount = $this->params['paging'][$model]['pageCount'];
				if ($modulus > $pageCount) {
					$modulus = $pageCount;
				}
				$start = $page - intval($modulus / 2);
				if ($start < 1) {
					$start = 1;
				}
				$end = $start + $modulus;
				if ($end > $pageCount) {
					$end = $pageCount + 1;
					$start = $end - $modulus;
				}
				for ($i = $start; $i < $end; $i++) {
					$url = array('page' => $i);
					$class = null;
					if ($i == $page) {
						$url = array();
						$class = 'active';
					}
					echo $this->Html->tag('li', $this->Paginator->link($i, $url), array(
						'class' => $class,
					));
				}
				?>
				
				<?php echo $this->Paginator->next('>', array(
					'tag' => 'li',
					'class' => 'next',
				), $this->Paginator->link('>', array()), array(
					'tag' => 'li',
					'escape' => false,
					'class' => 'next disabled',
				)); ?>
				
				<?php echo str_replace('<>', '', $this->Html->tag('li', $this->Paginator->last('>>', array(
					'tag' => null,
				)), array(
					'class' => 'next',
				))); ?>
			</ul>
		</div>
		<div class="pagination pull-right">
			<ul>
				<li class="disabled"><a><?php echo $this->I18n->i18nd("view","View");?>: </a></li>
				<?php
				/* Generate item limit customizer */
				foreach (array(15, 25, 50, 100) as $limit) {
					$options = ($pagecount == $limit) ? array('class' => 'active') : null;
					$text = $this->Html->link($limit, array('action' => 'pager', $limit));
					echo $this->Html->tag('li', $text, $options);
				}
				?>
			</ul>
		</div>
	</div><!--/pagination-container-->
<?php }
?>
</div>


<script type="text/javascript"> 
	$(function() {
		<?php
		
		foreach ($jsRecLookup as $url)
		{
			?>
			log('<?php echo $url?>');
			$.getJSON('<?php echo $url?>',function(data) {

				$.each(data, function (cid, result) {

					$('tr').each(function(){
						if (typeof $(this).data("state") =='undefined')
							$(this).data("state","unknown");

						var newhost ='<?php echo $_SERVER['SERVER_NAME']?>';
						
						if (typeof result.geo_id == 'undefined')
							result.geo_id = "n/a";
							
						
						if (cid == $(this).data("orig-id") ||cid == $(this).data("term-id") || result.geo_id == $(this).data("term-id") || result.geo_id == $(this).data("orig-id") )
						{
							
							var audioTag = '<audio id="audio-' +$(this).data("orig-id")+ '" '+
															'data-orig-id="' +$(this).data("orig-id")+ '"  data-term-id="' +$(this).data("term-id")+ '"'+
															'controls class="cdraudio" preload="<?php echo $this->Uiconfig->getUiConfig("PORTAL_CALLHISTORY_RECORDING_PRELOAD","metadata"); ?>" >';
							if (result.status.toLowerCase() =="converted" || result.status.toLowerCase() =="archived")
							{

								
								if ($(this).data("state")!= "available")
								{
									var parser = document.createElement('a');
									parser.href = result.url;
									if (typeof $(this).attr("recDomain") !='undefined' && $(this).attr("recDomain")!="")
									{
										newhost = parser.protocol+"//"+$(this).attr("recDomain")+parser.pathname+parser.search;
									}
									else
										newhost = result.url.replace("/localhost","/"+newhost);
									
									$(this).find('.listen.disabled').replaceWith('<a class="listen helpsy" title="Listen"></a>');
									//$(this).children('.action-buttons').append('<a class="listen helpsy" title="Listen"></a>');
									$(this).find('.download-audio.disabled').replaceWith('<a class="download-audio helpsy" title="Download" href="'+result.url.replace("/localhost","/<?php echo $_SERVER['SERVER_NAME']?>")+'" ></a>');
									// $(this).children('.action-buttons').prepend('<a class="download-audio helpsy" title="Download" href="'+result.url.replace("/localhost","/<?php echo $_SERVER['SERVER_NAME']?>")+'" ></a>');

									$(this).after('<tr class="audioplayerrow cdraudio hide"><td class="cdraudio" colspan="7">' +
										audioTag +
										'<source src="'+newhost+'&convert=wav16" type="audio/wav">' +
										'<source src="'+newhost+'&convert=aac" type="audio/mp4">'+
										'</audio>');
									$(this).data("state","available");
								}
								else
								{
									$(this).find('cdraudio').append('<td class="cdraudio" colspan="7">' +
										audioTag +
										'<source src="'+newhost+'&convert=wav16" type="audio/wav">' +
										'<source src="'+newhost+'&convert=aac" type="audio/mp4">'+
										'</audio>');
								}
								
								
								
								
							}
							else if (result.status.toLowerCase() =="unconverted")
							{
								
								$(this).find('.listen.disabled').replaceWith('<a class="listen disabled helpsy" title="Pending Conversion"></a>');
								//$(this).children('.action-buttons').append('<a class="listen disabled helpsy" title="Pending Conversion"></a>');
								
							}

							
							
							initTooltips();
							

							
						}
						
		
						});
						
					});
			    });

			<?php 
		}
		?>	
	});
	
	$('.table').on('click', 'a.listen',function(){
		//TODO:stop playing audio
		
		var audioRow = $(this).parents('tr').next('tr.cdraudio');
		
		
		if (audioRow.is(':hidden')) {
			$('tr.cdraudio').hide();
			audioRow.show();
		}
		else
			audioRow.hide();
		
		$('tr.cdraudio').hover(
			function () {
				$(this).prev('tr').css('background-color', '#f5f5f5');
			},
			function () {
				$(this).prev('tr').css('background-color', '#fff');
			}
		);
		
	});
</script>
		